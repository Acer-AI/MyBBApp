#ifndef COMPAT_QGLWIDGET_H
#define COMPAT_QGLWIDGET_H

// Minimal compatibility shim: if the code includes <QGLWidget> (Qt5),
// this header (placed in src/compat and added to include path) will
// provide a thin wrapper around QOpenGLWidget for Qt6.
#include <QOpenGLWidget>

// Provide a QGLWidget class name so existing code that includes <QGLWidget>
// compiles without change. Avoid Q_OBJECT here to keep moc out of the picture.
class QGLWidget : public QOpenGLWidget
{
public:
    explicit QGLWidget(QWidget *parent = nullptr) : QOpenGLWidget(parent) {}
    using QOpenGLWidget::QOpenGLWidget;
};

#endif // COMPAT_QGLWIDGET_H