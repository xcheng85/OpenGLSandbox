#include <ObjectGL.h>

using namespace OpenGLSandbox::GLWrapper;

ObjectGL::ObjectGL()
    : id_(~0)
{
    /*
    RenderContextSharedPtr current = RenderContext::getCurrentRenderContext();
    if (current)
    {
        m_shareGroup = current->getShareGroup();
    }*/
}

ObjectGL::~ObjectGL()
{
}

/*
ShareGroupSharedPtr Object::getShareGroup() const
{
    return (m_shareGroup);
}*/

GLuint ObjectGL::getGLId() const
{
    return id_;
}

void ObjectGL::setGLId(GLuint id)
{
    id_ = id;
}