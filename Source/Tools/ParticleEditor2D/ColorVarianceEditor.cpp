//
// Copyright (c) 2014 the ParticleEditor2D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include "FloatEditor.h"
#include "ColorVarianceEditor.h"
#include <QComboBox>
#include <QGroupBox>

namespace Urho3D
{

ColorVarianceEditor::ColorVarianceEditor(const QString& text) :
    QGroupBox(text)
{
    QVBoxLayout* vBoxLayout = new QVBoxLayout();
    setLayout(vBoxLayout);

    colorModeComboBox_ = new QComboBox();
    vBoxLayout->addWidget(colorModeComboBox_);

    colorModeComboBox_->addItem(tr("One Color Mode"));
    colorModeComboBox_->addItem(tr("Random Color Mode"));
    colorModeComboBox_->setCurrentIndex(-1);

    connect(colorModeComboBox_, SIGNAL(currentIndexChanged(int)), this, SLOT(colorModeComboBoxIndexChanged(int)));

    frame_ = new QFrame();
    vBoxLayout->addWidget(frame_);
    frame_->setFixedHeight(20);
    frame_->setAutoFillBackground(true);
    
    minColorGroupBox_ = new QGroupBox(tr("Color 1"));
    vBoxLayout->addWidget(minColorGroupBox_);
    QVBoxLayout* minColorVBoxLayout = new QVBoxLayout();
    minColorGroupBox_->setLayout(minColorVBoxLayout);
    minColorVBoxLayout->addLayout(minREditor_ = CreateFloatEditor("R"));
    minColorVBoxLayout->addLayout(minGEditor_ = CreateFloatEditor("G"));
    minColorVBoxLayout->addLayout(minBEditor_ = CreateFloatEditor("B"));
    minColorVBoxLayout->addLayout(minAEditor_ = CreateFloatEditor("A"));

    maxColorGroupBox_ = new QGroupBox(tr("Color 2"));
    vBoxLayout->addWidget(maxColorGroupBox_ );
    QVBoxLayout* maxColorVBoxLayout = new QVBoxLayout();
    maxColorGroupBox_->setLayout(maxColorVBoxLayout );

    maxColorVBoxLayout->addLayout(maxREditor_ = CreateFloatEditor("R"));
    maxColorVBoxLayout->addLayout(maxGEditor_ = CreateFloatEditor("G"));
    maxColorVBoxLayout->addLayout(maxBEditor_ = CreateFloatEditor("B"));
    maxColorVBoxLayout->addLayout(maxAEditor_ = CreateFloatEditor("A"));
}

ColorVarianceEditor::~ColorVarianceEditor()
{   
}

void ColorVarianceEditor::setValue(const Color& value, const Color& variance)
{
    Color min = value - variance;
    Color max = value + variance;

    minREditor_->setValue(min.r_);
    minGEditor_->setValue(min.g_);
    minBEditor_->setValue(min.b_);
    minAEditor_->setValue(min.a_);

    maxREditor_->setValue(max.r_);
    maxGEditor_->setValue(max.g_);
    maxBEditor_->setValue(max.b_);
    maxAEditor_->setValue(max.a_);

    colorModeComboBox_->setCurrentIndex(variance == Color::TRANSPARENT ? 0 : 1);
}

Color ColorVarianceEditor::avarage() const
{
    Color min = Color(minREditor_->value(), minGEditor_->value(), minBEditor_->value(), minAEditor_->value());
    Color max = Color(maxREditor_->value(), maxGEditor_->value(), maxBEditor_->value(), maxAEditor_->value());
    return (min + max) * 0.5f;
}

Color ColorVarianceEditor::variance() const
{
    Color min = Color(minREditor_->value(), minGEditor_->value(), minBEditor_->value(), minAEditor_->value());
    Color max = Color(maxREditor_->value(), maxGEditor_->value(), maxBEditor_->value(), maxAEditor_->value());
    return (max - min) * 0.5f;
}

void ColorVarianceEditor::editorValueChanged()
{   
    Color min = Color(minREditor_->value(), minGEditor_->value(), minBEditor_->value(), minAEditor_->value());
    Color max = Color(maxREditor_->value(), maxGEditor_->value(), maxBEditor_->value(), maxAEditor_->value());

    if (colorModeComboBox_->currentIndex() == 0)
        max = min;

    QColor qMinColor = QColor::fromRgbF(min.r_, min.g_, min.b_, min.a_);
    QColor qMaxColor = QColor::fromRgbF(max.r_, max.g_, max.b_, max.a_);
    char styleSheet[256];
    sprintf(styleSheet, "background-color: qlineargradient(x1:0, y1:0.5, x2:1, y2:0.5, stop:0 rgba(%d, %d, %d, %d), stop:1 rgba(%d, %d, %d, %d))", 
        qMinColor.red(), qMinColor.green(), qMinColor.blue(), qMinColor.alpha(),
        qMaxColor.red(), qMaxColor.green(), qMaxColor.blue(), qMaxColor.alpha());

    frame_->setStyleSheet(styleSheet);

    emit valueChanged((min + max) * 0.5f, (max - min) * 0.5f);
}

void ColorVarianceEditor::colorModeComboBoxIndexChanged(int index)
{
    maxColorGroupBox_->setVisible(index != 0);
    editorValueChanged();
}

FloatEditor* ColorVarianceEditor::CreateFloatEditor(const QString& text)
{
    FloatEditor* editor = new FloatEditor(text, false);
    editor->setRange(0.0f, 1.0f);
    connect(editor, SIGNAL(valueChanged(float)), this, SLOT(editorValueChanged()));
    return editor;
}

}