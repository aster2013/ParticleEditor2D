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

#include "ParticleEffectEditor.h"
#include "ScrollAreaWidget.h"

class QComboBox;
class QLineEdit;

namespace Urho3D
{

class FloatEditor;
class IntEditor;
class ValueVarianceEditor;
class Vector2Editor;

class EmitterAttributeEditor : public ScrollAreaWidget, public ParticleEffectEditor
{
    Q_OBJECT
        OBJECT(EmitterAttributeEditor)

public:
    EmitterAttributeEditor(Context* context);
    virtual ~EmitterAttributeEditor();

private slots:
    void HandleMaxParticlesEditorValueChanged(int value);
    void HandleDurationEditorValueChanged(float value);    
    void HandleTexturePushButtonClicked();
    void HandleBlendModeEditorChanged(int index);
    
    void HandleEmitterTypeEditorChanged(int index);
    void HandleSourcePositionVarianceEditorValueChanged(const Vector2& value);
    void HandleGravityEditorValueChanged(const Vector2& value);

    void HandleValueVarianceEditorValueChanged(float average, float variance);

private:
    virtual void HandleUpdateWidget();

    void CreateMaxParticlesEditor();
    void CreateDurationEditor();
    void CreateTextureEditor();
    void CreateBlendModeEditor();

    void CreateEmitterTypeEditor();
    void CreateGravityTypeEditor();
    void CreateRadialTypeEditor();
    void ShowRadialTypeEditor(bool visible);
    void ShowGravityTypeEditor(bool visible);
    ValueVarianceEditor* CreateValueVarianceEditor(const QString& name, float min, float max);

    void HandlePostUpdate(StringHash eventType, VariantMap& eventData);

    /// Max particle editor.
    IntEditor* maxParticlesEditor_;
    /// Is max particles changed.
    bool maxParticlesChanged_;
    /// Duration editor.
    FloatEditor* durationEditor_;
    /// Texture editor.
    QLineEdit* textureEditor_;
    /// Blend mode editor.
    QComboBox* blendModeEditor_;
    /// Emitter type editor.
    QComboBox* emitterTypeEditor_;


    /// Source position variance editor.
    Vector2Editor* sourcePositionVarianceEditor_;
    /// Speed editor.
    ValueVarianceEditor* speedEditor_;
    /// Angle editor.
    ValueVarianceEditor* angleEditor_;
    /// Gravity editor.
    Vector2Editor* gravityEditor_;
    /// Radial acceleration editor.
    ValueVarianceEditor* radialAccelerationEditor_;
    /// Tangential acceleration editor.
    ValueVarianceEditor* tangentialAccelerationEditor_;

    /// Max radius editor.
    ValueVarianceEditor* maxRadiusEditor_;
    /// Min radius editor.
    ValueVarianceEditor* minRadiusEditor_;
    /// Rotate per second editor.
    ValueVarianceEditor* rotatePerSecondEditor_;
};

}
