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

#include "IntEditor.h"
#include <QLabel>
#include <QSpinBox>
#include <QSlider>

namespace Urho3D
{

IntEditor::IntEditor(const QString& text) :
    senderIsSlider_(false),
    senderIsSpinBox_(false)
{
    setContentsMargins(0, 0, 0, 0);

    label_ = new QLabel(text);
    addWidget(label_, 0);

    slider_ = new QSlider(Qt::Horizontal);
    addWidget(slider_, 1);
    connect(slider_, SIGNAL(valueChanged(int)), this, SLOT(sliderValueChanged(int)));

    spinBox_ = new QSpinBox;
    addWidget(spinBox_);
    connect(spinBox_, SIGNAL(valueChanged(int)), this, SLOT(spinBoxValueChanged(int)));
}

IntEditor::~IntEditor()
{
    delete label_;
    delete slider_;
    delete spinBox_;
}

void IntEditor::setValue(int value)
{
    spinBox_->setValue(value);
}

void IntEditor::setRange(int min, int max)
{
    slider_->setRange(min, max);
    spinBox_->setRange(min, max);
}

int IntEditor::value() const
{
    return (int)spinBox_->value();
}

void IntEditor::sliderValueChanged(int value)
{
    senderIsSlider_ = true;

    if (!senderIsSpinBox_)
        spinBox_->setValue(value);

    senderIsSlider_ = false;
}

void IntEditor::spinBoxValueChanged(int value)
{
    senderIsSpinBox_ = true;

    if (!senderIsSlider_)
        slider_->setValue(value);

    senderIsSpinBox_ = false;

    emit valueChanged(value);
}

}