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
#include <QLabel>
#include <QDoubleSpinBox>
#include <QSlider>

namespace Urho3D
{

FloatEditor::FloatEditor(const QString& text, bool setLabelWidth) :
    senderIsSlider_(false),
    senderIsSpinBox_(false)
{
    setContentsMargins(0, 0, 0, 0);

    label_ = new QLabel(text);
    if (setLabelWidth)
        label_->setFixedWidth(120);

    addWidget(label_, 0);

    slider_ = new QSlider(Qt::Horizontal);
    addWidget(slider_, 1);
    
    connect(slider_, SIGNAL(valueChanged(int)), this, SLOT(sliderValueChanged(int)));

    spinBox_ = new QDoubleSpinBox;
    spinBox_->setFixedWidth(60);
    spinBox_->setButtonSymbols(QDoubleSpinBox::NoButtons);
    addWidget(spinBox_);

    connect(spinBox_, SIGNAL(valueChanged(double)), this, SLOT(spinBoxValueChanged(double)));
}

FloatEditor::~FloatEditor()
{
    delete label_;
    delete slider_;
    delete spinBox_;
}

void FloatEditor::setValue(float value)
{
    senderIsSlider_ = true;
    senderIsSpinBox_ = true;

    spinBox_->setValue(value);
    setSliderValue(value);

    senderIsSlider_ = false;
    senderIsSpinBox_ = false;
}

void FloatEditor::setRange(float min, float max)
{
    spinBox_->setRange(min, max);

    double delta = (max - min) * 0.01;
    if (delta > 1.0)
        delta = 1.0;
    spinBox_->setSingleStep(delta);
}

float FloatEditor::value() const
{
    return (float)spinBox_->value();
}

void FloatEditor::sliderValueChanged(int value)
{
    senderIsSlider_ = true;

    if (!senderIsSpinBox_)
    {
        int sliderMin = slider_->minimum();
        int sliderMax = slider_->maximum();

        double spinBoxMin = spinBox_->minimum();
        double spinBoxMax = spinBox_->maximum();

        double spinBoxValue = spinBoxMin + (spinBoxMax - spinBoxMin) / (sliderMax -  sliderMin) * (value - sliderMin);
        spinBox_->setValue(spinBoxValue);
    }

    senderIsSlider_ = false;
}

void FloatEditor::spinBoxValueChanged(double value)
{
    senderIsSpinBox_ = true;

    if (!senderIsSlider_)
        setSliderValue(value);

    senderIsSpinBox_ = false;

    emit valueChanged(value);
}

void FloatEditor::setSliderValue(double value)
{
    double spinBoxMin = spinBox_->minimum();
    double spinBoxMax = spinBox_->maximum();

    int sliderMin = slider_->minimum();
    int sliderMax = slider_->maximum();

    int sliderValue = (int)(sliderMin + (sliderMax -  sliderMin) / (spinBoxMax - spinBoxMin) * (value - spinBoxMin));
    slider_->setValue(sliderValue);
}

}