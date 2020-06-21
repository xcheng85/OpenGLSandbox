#pragma once

#include <GL/glew.h>

namespace OpenGLSandbox
{
    namespace GLWrapper
    {
        class ObjectGL
        {
        public:
            GLuint getGLId() const;

        protected:
            ObjectGL();
            virtual ~ObjectGL();

            // DP_GL_API ShareGroupSharedPtr getShareGroup() const;
            void setGLId(GLuint id);

        protected:
            GLuint id_; //!< OpenGL id

        private:
            // ShareGroupSharedPtr m_shareGroup; //!< The share group holding this object
        };
    }; // namespace GLWrapper
};     // namespace OpenGLSandbox