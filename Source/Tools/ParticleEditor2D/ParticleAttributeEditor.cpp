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

#include "ColorVarianceEditor.h"
#include "ParticleAttributeEditor.h"
#include "ParticleEffect2D.h"
#include "ValueVarianceEditor.h"
#include <QVBoxLayout>

namespace Urho3D
{
ParticleAttributeEditor::ParticleAttributeEditor(Context* context) :
    ParticleEffectEditor(context)
{
    particleLifeSpanEditor_ = CreateValueVarianceEditor(tr("Life Span"), 0.01f, 10.0f);
    
    startSizeEditor_ = CreateValueVarianceEditor(tr("Start Size"), 0.0f, 100.0f);
    finishSizeEditor_ = CreateValueVarianceEditor(tr("Finish Size"), 0.0f, 100.0f);
    
    startRotationEditor_ = CreateValueVarianceEditor(tr("Start Rotation"), 0.0f, 360.0f);
    finishRotationEditor_ = CreateValueVarianceEditor(tr("Finish Rotation"), 0.0f, 360.0f);

    startColorEditor_ = new ColorVarianceEditor(tr("Start Color"));
    vBoxLayout_->addWidget(startColorEditor_);
    connect(startColorEditor_, SIGNAL(valueChanged(const Color&, const Color&)), this, SLOT(HandleStartColorEditorValueChanged(const Color&, const Color&)));

    finishColorEditor_ = new ColorVarianceEditor(tr("Finish Color"));
    vBoxLayout_->addWidget(finishColorEditor_);
    connect(finishColorEditor_, SIGNAL(valueChanged(const Color&, const Color&)), this, SLOT(HandleFinishColorEditorValueChanged(const Color&, const Color&)));

    vBoxLayout_->addStretch(1);
}

ParticleAttributeEditor::~ParticleAttributeEditor()
{
}

void ParticleAttributeEditor::HanldeValueVarianceEditorValueChanged(float average, float variance)
{
    if (updatingWidget_)
        return;

    ParticleEffect2D* effect = GetEffect();
    QObject* s = sender();
    if (s == particleLifeSpanEditor_)
    {
        effect->SetParticleLifeSpan(average);
        effect->SetParticleLifespanVariance(variance);
    }
    else if (s == startSizeEditor_)
    {
        effect->SetStartParticleSize(average);
        effect->SetStartParticleSizeVariance(variance);
    }
    else if (s == finishSizeEditor_)
    {
        effect->SetFinishParticleSize(average);
        effect->SetFinishParticleSizeVariance(variance);
    }
    else if (s == startRotationEditor_)
    {
        effect->SetRotationStart(average);
        effect->SetRotationStartVariance(variance);
    }
    else if (s == finishRotationEditor_)
    {
        effect->SetRotationEnd(average);
        effect->SetRotationEndVariance(variance);
    }
}


void ParticleAttributeEditor::HandleUpdateWidget()
{
    ParticleEffect2D* effect = GetEffect();

    particleLifeSpanEditor_->setValue(effect->GetParticleLifeSpan(), effect->GetParticleLifespanVariance());

    startSizeEditor_->setValue(effect->GetStartParticleSize(), effect->GetStartParticleSizeVariance());
    finishSizeEditor_->setValue(effect->GetFinishParticleSize(), effect->GetFinishParticleSizeVariance());
    
    startRotationEditor_->setValue(effect->GetRotationStart(), effect->GetRotationStartVariance());
    finishRotationEditor_->setValue(effect->GetRotationEnd(), effect->GetRotationEndVariance());

    const Color& startColor = effect->GetStartColor();
    const Color& startColorVariance = effect->GetStartColorVariance();
    startColorEditor_->setValue(startColor, startColorVariance);
    
    const Color& finishColor = effect->GetFinishColor();
    const Color& finishColorVariance = effect->GetFinishColorVariance();
    finishColorEditor_->setValue(finishColor, finishColorVariance);
}

ValueVarianceEditor* ParticleAttributeEditor::CreateValueVarianceEditor(const QString& name, float min, float max)
{
    ValueVarianceEditor* editor = new ValueVarianceEditor(name);
    editor->setRange(min, max);
    vBoxLayout_->addWidget(editor);
    connect(editor, SIGNAL(valueChanged(float, float)), this, SLOT(HanldeValueVarianceEditorValueChanged(float, float)));
    return editor;
}


void ParticleAttributeEditor::HandleStartColorEditorValueChanged(const Color& average, const Color& variance)
{
    if (updatingWidget_)
        return;
    ParticleEffect2D* effect = GetEffect();
    effect->SetStartColor(average);
    effect->SetStartColorVariance(variance);
}

void ParticleAttributeEditor::HandleFinishColorEditorValueChanged(const Color& average, const Color& variance)
{
    if (updatingWidget_)
        return;

    ParticleEffect2D* effect_ = GetEffect();
    effect_->SetFinishColor(average);
    effect_->SetFinishColorVariance(variance);
}
}