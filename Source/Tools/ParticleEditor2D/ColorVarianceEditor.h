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

#pragma once

#include "Color.h"
#include <QGroupBox>

class QComboBox;
class QFrame;

namespace Urho3D
{
class FloatEditor;

class ColorVarianceEditor : public QGroupBox
{
    Q_OBJECT

public:
    ColorVarianceEditor(const QString& text);
    virtual ~ColorVarianceEditor();

public:
    /// Set value.
    void setValue(const Color& avarage, const Color& variance);
    /// Return value.
    Color avarage() const;
    Color variance() const;

signals:
    void valueChanged(const Color& avarage, const Color& variance);

protected slots:
    void colorModeComboBoxIndexChanged(int index);
    void editorValueChanged();

private:
    FloatEditor* CreateFloatEditor(const QString& text);

    QComboBox* colorModeComboBox_;

    QFrame* frame_;

    QGroupBox* minColorGroupBox_;
    FloatEditor* minREditor_;
    FloatEditor* minGEditor_;
    FloatEditor* minBEditor_;
    FloatEditor* minAEditor_;

    QGroupBox* maxColorGroupBox_;
    FloatEditor* maxREditor_;
    FloatEditor* maxGEditor_;
    FloatEditor* maxBEditor_;
    FloatEditor* maxAEditor_;
};

}