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

#include "Camera.h"
#include "Console.h"
#include "Context.h"
#include "CoreEvents.h"
#include "DebugHud.h"
#include "DebugRenderer.h"
#include "Engine.h"
#include "Graphics.h"
#include "Input.h"
#include "InputEvents.h"
#include "Log.h"
#include "MainWindow.h"
#include "Octree.h"
#include "ParticleEditor.h"
#include "ParticleEffect2D.h"
#include "ParticleEmitter2D.h"
#include "ProcessUtils.h"
#include "Renderer.h"
#include "ResourceCache.h"
#include "Scene.h"
#include "Viewport.h"
#include "XMLFile.h"
#include <QFile>
#include <QTimer>

namespace Urho3D
{

ParticleEditor::ParticleEditor(int argc, char** argv, Context* context) :
    QApplication(argc, argv),
    Object(context),
    engine_(new Engine(context_)),
    scene_(new Scene(context_)),
    mainWindow_(new MainWindow(context_))
{
    SubscribeToEvent(E_UPDATE, HANDLER(ParticleEditor, HandleUpdate));
    SubscribeToEvent(E_KEYDOWN, HANDLER(ParticleEditor, HandleKeyDown));
    SubscribeToEvent(E_MOUSEWHEEL, HANDLER(ParticleEditor, HandleMouseWheel));
    SubscribeToEvent(E_RENDERUPDATE, HANDLER(ParticleEditor, HandleRenderUpdate));
}

ParticleEditor::~ParticleEditor()
{
    delete mainWindow_;
}

int ParticleEditor::Run()
{
    VariantMap engineParameters;
    engineParameters["FrameLimiter"] = false;
    engineParameters["LogName"] = "ParticleEditor2D.log";
    engineParameters["ExternalWindow"] = (void*)(mainWindow_->centralWidget()->winId());
    if (!engine_->Initialize(engineParameters))
        return -1;

    CreateScene();
    CreateConsole();
    CreateDebugHud();

    mainWindow_->CreateWidgets();
    
    New();

    QTimer timer;
    connect(&timer, SIGNAL(timeout()), this, SLOT(OnTimeout()));
    timer.start(16);

    return QApplication::exec();
}

void ParticleEditor::New()
{
    Open("Urho2D/fire.pex");

    fileName_.Clear();
}

void ParticleEditor::Open(const String& fileName)
{
    if (particleNode_)
    {
        particleNode_->Remove();
        particleNode_ = 0;
    }

    ResourceCache* cache = GetSubsystem<ResourceCache>();
    ParticleEffect2D* particleEffect = cache->GetResource<ParticleEffect2D>(fileName);
    if (!particleEffect)
    {
        LOGERROR("Open particle effect failed " + fileName);
        return;
    }

    fileName_ = fileName;

    particleNode_ = scene_->CreateChild("ParticleEmitter2D");
    ParticleEmitter2D* particleEmitter = particleNode_->CreateComponent<ParticleEmitter2D>();
    particleEmitter->SetEffect(particleEffect);

    mainWindow_->UpdateWidget();
}

void ParticleEditor::Save(const String& fileName)
{
    ParticleEffect2D* particleEffect = GetEffect();
    if (!particleEffect)
        return;

    File file(context_);
    if (!file.Open(fileName, FILE_WRITE))
    {
        LOGERROR("Open file failed " + fileName);
        return;
    }

    particleEffect->Save(file);

    fileName_ = fileName;
}

Camera* ParticleEditor::GetCamera() const
{
    return cameraNode_->GetComponent<Camera>();
}

ParticleEffect2D* ParticleEditor::GetEffect() const
{
    ParticleEmitter2D* emitter = GetEmitter();
    if (!emitter)
        return 0;

    return emitter->GetEffect();
}


ParticleEmitter2D* ParticleEditor::GetEmitter() const
{
    return particleNode_->GetComponent<ParticleEmitter2D>();
}


ParticleEditor* ParticleEditor::Get()
{
    return qobject_cast<ParticleEditor*>(qApp);
}

void ParticleEditor::OnTimeout()
{
    if (engine_ && !engine_->IsExiting())
        engine_->RunFrame();
}

void ParticleEditor::CreateScene()
{
    scene_ = new Scene(context_);
    scene_->CreateComponent<Octree>();
    scene_->CreateComponent<DebugRenderer>();

    // Create camera.
    cameraNode_ = scene_->CreateChild("Camera");
    Camera* camera = cameraNode_->CreateComponent<Camera>();

    camera->SetOrthographic(true);
    Graphics* graphic = GetSubsystem<Graphics>();
    camera->SetOrthoSize(graphic->GetHeight() * PIXEL_SIZE);

    SharedPtr<Viewport> viewport(new Viewport(context_, scene_, camera));

    Renderer* renderer = GetSubsystem<Renderer>();
    renderer->SetViewport(0, viewport);

    New();
}

void ParticleEditor::CreateConsole()
{
    // Get default style
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    XMLFile* xmlFile = cache->GetResource<XMLFile>("UI/DefaultStyle.xml");

    // Create console
    Console* console = engine_->CreateConsole();
    console->SetDefaultStyle(xmlFile);
}

void ParticleEditor::CreateDebugHud()
{
    // Get default style
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    XMLFile* xmlFile = cache->GetResource<XMLFile>("UI/DefaultStyle.xml");

    // Create debug HUD.
    DebugHud* debugHud = engine_->CreateDebugHud();
    debugHud->SetDefaultStyle(xmlFile);
}

void ParticleEditor::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace Update;

    // Take the frame time step, which is stored as a float
    float timeStep = eventData[P_TIMESTEP].GetFloat();
    Input* input = GetSubsystem<Input>();

    // When left button is down, move mouse to particle node
    if (input->GetMouseButtonDown(MOUSEB_LEFT) && particleNode_)
    {
        IntVector2 mousePosition = input->GetMousePosition();

        Graphics* graphics = GetSubsystem<Graphics>();
        Vector3 screenPoint((float)mousePosition.x_ / graphics->GetWidth(), (float)mousePosition.y_ / graphics->GetHeight(), 0.0f);

        Camera* camera = cameraNode_->GetComponent<Camera>();
        Vector3 worldPoint = camera->ScreenToWorldPoint(screenPoint);
        particleNode_->SetPosition(worldPoint);
    }
}

void ParticleEditor::HandleKeyDown(StringHash eventType, VariantMap& eventData)
{
    using namespace KeyDown;
    int key = eventData[P_KEY].GetInt();
    if (key == KEY_F1)
        GetSubsystem<Console>()->Toggle();
    else if (key == KEY_F2)
        GetSubsystem<DebugHud>()->ToggleAll();
}

void ParticleEditor::HandleMouseWheel(StringHash eventType, VariantMap& eventData)
{
    using namespace MouseWheel;

    int wheel = eventData[P_WHEEL].GetInt();
    Camera* camera = cameraNode_->GetComponent<Camera>();
    if (wheel > 0)
        camera->SetZoom(camera->GetZoom() * 1.25f);
    else
        camera->SetZoom(camera->GetZoom() * 0.80f);
}

void ParticleEditor::HandleRenderUpdate(StringHash eventType, VariantMap& eventData)
{
    Camera* camera = cameraNode_->GetComponent<Camera>();
    const float value = 20.0f / camera->GetZoom();
    const Color color(0.0f, 0.5f, 0.0f, 0.5f);
    
    DebugRenderer* debugRenderer = scene_->GetComponent<DebugRenderer>();
    debugRenderer->AddLine(Vector3(-value, 0.0f, 1.0f), Vector3(value, 0.0f, 1.0f), color);
    debugRenderer->AddLine(Vector3(0.0f, -value, 1.0f), Vector3(0.0f, value, 1.0f), color);
    debugRenderer->Render();
}

}
