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

#include "Object.h"
#include "Ptr.h"
#include <QApplication>

namespace Urho3D
{

class Camera;
class Context;
class Engine;
class MainWindow;
class Node;
class ParticleEffect2D;
class ParticleEmitter2D;
class Scene;

/// Particle editor class.
class ParticleEditor : public QApplication, public Object
{
    Q_OBJECT
    OBJECT(ParticleEditor)

public:
    /// Construct.
    ParticleEditor(int argc, char** argv, Context* context);
    /// Destruct.
    virtual ~ParticleEditor();

    /// Run.
    int Run();

    void New();
    void Open(const String& fileName);
    void Save(const String& fileName);

    const String& GetFileName() const { return fileName_; }
    /// Return camera.
    Camera* GetCamera() const;
    /// Return effect.
    ParticleEffect2D* GetEffect() const;
    /// Return emitter.
    ParticleEmitter2D* GetEmitter() const;

    /// Return editor pointer.
    static ParticleEditor* Get();

private slots:
    // Timeout handler.
    void OnTimeout();

private:
    /// Create scene.
    void CreateScene();
    /// Create console.
    void CreateConsole();
    /// Create debug HUD.
    void CreateDebugHud();
    /// Handle update event.
    void HandleUpdate(StringHash eventType, VariantMap& eventData);
    /// Handle key down (toggle debug HUD).
    void HandleKeyDown(StringHash eventType, VariantMap& eventData);
    /// Handle mouse wheel.
    void HandleMouseWheel(StringHash eventType, VariantMap& eventData);
    /// Handle render update.
    void HandleRenderUpdate(StringHash eventType, VariantMap& eventData);

    /// Editor main window.
    MainWindow* mainWindow_;
    /// Engine.
    SharedPtr<Engine> engine_;
    /// Scene.
    SharedPtr<Scene> scene_;
    /// File name
    String fileName_;
    /// Camera node.
    SharedPtr<Node> cameraNode_;
    /// Particle node.
    SharedPtr<Node> particleNode_;
};

}
