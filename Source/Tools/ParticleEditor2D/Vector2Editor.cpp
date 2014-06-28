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
#include "Vector2Editor.h"
#include <QGroupBox>

namespace Urho3D
{
    
Vector2Editor::Vector2Editor(const QString& text) :
    QGroupBox(text)
{
    QVBoxLayout* vBoxLayout = new QVBoxLayout();
    setLayout(vBoxLayout);

    xEditor_ = new FloatEditor("X", false);
    vBoxLayout->addLayout(xEditor_);
    connect(xEditor_, SIGNAL(valueChanged(float)), this, SLOT(editorValueChanged()));

    yEditor_ = new FloatEditor("Y", false);
    vBoxLayout->addLayout(yEditor_);
    connect(yEditor_, SIGNAL(valueChanged(float)), this, SLOT(editorValueChanged()));
}

Vector2Editor::~Vector2Editor()
{
    delete xEditor_;
    delete yEditor_;
}


void Vector2Editor::setValue(const Vector2& value)
{
    xEditor_->setValue(value.x_);
    yEditor_->setValue(value.y_);
}

Vector2 Vector2Editor::value() const
{
    return Vector2(xEditor_->value(), yEditor_->value());
}

void Vector2Editor::setRange(const Vector2& min, const Vector2& max)
{
    xEditor_->setRange(min.x_, max.x_);
    yEditor_->setRange(min.y_, max.y_);
}

void Vector2Editor::editorValueChanged()
{
    emit valueChanged(value());
}

}