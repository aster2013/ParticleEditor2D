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
#include "ValueVarianceEditor.h"
#include <QGroupBox>
#include <QLabel>

namespace Urho3D
{
    
ValueVarianceEditor::ValueVarianceEditor(const QString& text) :
    QGroupBox(text)
{
    QVBoxLayout* vBoxLayout = new QVBoxLayout();
    setLayout(vBoxLayout);

    averageEditor_ = new FloatEditor(tr("Value"), false);
    vBoxLayout->addLayout(averageEditor_);

    averageEditor_->label()->setFixedWidth(64);
    connect(averageEditor_, SIGNAL(valueChanged(float)), this, SLOT(editorValueChanged()));

    varianceEditor_ = new FloatEditor(tr("Variance"), false);
    vBoxLayout->addLayout(varianceEditor_);

    varianceEditor_->label()->setFixedWidth(64);
    connect(varianceEditor_, SIGNAL(valueChanged(float)), this, SLOT(editorValueChanged()));
}

ValueVarianceEditor::~ValueVarianceEditor()
{
    delete averageEditor_;
    delete varianceEditor_;
}

void ValueVarianceEditor::setValue(float avarage, float variance)
{
    averageEditor_->setValue(avarage);
    varianceEditor_->setValue(variance);
}


void ValueVarianceEditor::editorValueChanged()
{
    emit valueChanged(value(), variance());
}

void ValueVarianceEditor::setRange(float min, float max)
{
    averageEditor_->setRange(min, max);
    varianceEditor_->setRange(0.0f, max - min);
}

float ValueVarianceEditor::value() const
{
    return averageEditor_->value();
}

float ValueVarianceEditor::variance() const
{
    return varianceEditor_->value();
}

}