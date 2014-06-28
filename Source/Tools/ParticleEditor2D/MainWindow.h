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

#include "Object.h"
#include "ParticleEffectEditor.h"
#include "Ptr.h"
#include <QMainWindow>
#include <QMap>

class QAction;
class QActionGroup;
class QMenu;

namespace Urho3D
{

class EmitterAttributeEditor;
class ParticleAttributeEditor;
class ScrollAreaWidget;

/// Editor main window class.
class MainWindow : public QMainWindow, public ParticleEffectEditor
{
    Q_OBJECT
    OBJECT(MainWindow)

public:
    /// Construct.
    MainWindow(Context* context);
    
    /// Create widgets.
    void CreateWidgets();

private:
    /// Handle update widget.
    virtual void HandleUpdateWidget();

    /// Create actions.
    void CreateActions();
    // Create menu bar.
    void CreateMenuBar();
    /// Create toolbar.
    void CreateToolBar();
    /// Create dock widgets.
    void CreateDockWidgets();

private slots:
    /// Handle new action.
    void HandleNewAction();
    /// Handle open action.
    void HandleOpenAction();
    /// Handle save action.
    void HandleSaveAction();
    /// Handle save as action.
    void HandleSaveAsAction();
    /// Handle zoom action.
    void HandleZoomAction();
    /// Handle background action.
    void HandleBackgroundAction();

private:
    /// New action.
    QAction* newAction_;
    /// Open action.
    QAction* openAction_;
    /// Save action.
    QAction* saveAction_;
    /// Save action.
    QAction* saveAsAction_;
    /// Exit action.
    QAction* exitAction_;
    /// Zoom in action.
    QAction* zoomInAction_;
    /// Zoom out action.
    QAction* zoomOutAction_;
    /// Zoom reset action.
    QAction* zoomResetAction_;
    /// Background action;
    QAction* backgroundAction_;
    /// File menu.
    QMenu* fileMenu_;
    /// View menu.
    QMenu* viewMenu_;
    /// Tool bar.
    QToolBar* toolBar_;
    /// Inspector window.
    EmitterAttributeEditor* emitterAttributeEditor_;
    /// Inspector window.
    ParticleAttributeEditor* particleAttributeEditor_;
};

}
