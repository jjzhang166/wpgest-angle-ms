//
// Copyright 2015 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// RendererGL.cpp: Implements the class methods for RendererGL.

#include "libANGLE/renderer/gl/RendererGL.h"

#include "common/debug.h"
#include "libANGLE/Data.h"
#include "libANGLE/renderer/gl/BufferGL.h"
#include "libANGLE/renderer/gl/CompilerGL.h"
#include "libANGLE/renderer/gl/DefaultAttachmentGL.h"
#include "libANGLE/renderer/gl/FenceNVGL.h"
#include "libANGLE/renderer/gl/FenceSyncGL.h"
#include "libANGLE/renderer/gl/FramebufferGL.h"
#include "libANGLE/renderer/gl/FunctionsGL.h"
#include "libANGLE/renderer/gl/ProgramGL.h"
#include "libANGLE/renderer/gl/QueryGL.h"
#include "libANGLE/renderer/gl/RenderbufferGL.h"
#include "libANGLE/renderer/gl/ShaderGL.h"
#include "libANGLE/renderer/gl/StateManagerGL.h"
#include "libANGLE/renderer/gl/TextureGL.h"
#include "libANGLE/renderer/gl/TransformFeedbackGL.h"
#include "libANGLE/renderer/gl/VertexArrayGL.h"
#include "libANGLE/renderer/gl/renderergl_utils.h"

namespace rx
{

RendererGL::RendererGL(const FunctionsGL *functions)
    : Renderer(),
      mFunctions(functions),
      mStateManager(nullptr)
{
    ASSERT(mFunctions);
    mStateManager = new StateManagerGL(mFunctions);
}

RendererGL::~RendererGL()
{
    SafeDelete(mStateManager);
}

gl::Error RendererGL::flush()
{
    UNIMPLEMENTED();
    return gl::Error(GL_INVALID_OPERATION);
}

gl::Error RendererGL::finish()
{
    UNIMPLEMENTED();
    return gl::Error(GL_INVALID_OPERATION);
}

gl::Error RendererGL::drawArrays(const gl::Data &data, GLenum mode,
                                 GLint first, GLsizei count, GLsizei instances)
{
    mStateManager->setDrawState(*data.state);
    mFunctions->drawArrays(mode, first, count);

    return gl::Error(GL_NO_ERROR);
}

gl::Error RendererGL::drawElements(const gl::Data &data, GLenum mode, GLsizei count, GLenum type,
                                   const GLvoid *indices, GLsizei instances,
                                   const RangeUI &indexRange)
{
    if (instances > 0)
    {
        UNIMPLEMENTED();
    }

    mStateManager->setDrawState(*data.state);
    mFunctions->drawElements(mode, count, type, indices);

    return gl::Error(GL_NO_ERROR);
}

CompilerImpl *RendererGL::createCompiler(const gl::Data &data)
{
    return new CompilerGL(data);
}

ShaderImpl *RendererGL::createShader(GLenum type)
{
    return new ShaderGL(type, mFunctions);
}

ProgramImpl *RendererGL::createProgram()
{
    return new ProgramGL(mFunctions, mStateManager);
}

DefaultAttachmentImpl *RendererGL::createDefaultAttachment(GLenum type, egl::Surface *surface)
{
    return new DefaultAttachmentGL();
}

FramebufferImpl *RendererGL::createFramebuffer()
{
    return new FramebufferGL();
}

TextureImpl *RendererGL::createTexture(GLenum target)
{
    return new TextureGL();
}

RenderbufferImpl *RendererGL::createRenderbuffer()
{
    return new RenderbufferGL();
}

BufferImpl *RendererGL::createBuffer()
{
    return new BufferGL(mFunctions, mStateManager);
}

VertexArrayImpl *RendererGL::createVertexArray()
{
    return new VertexArrayGL(mFunctions, mStateManager);
}

QueryImpl *RendererGL::createQuery(GLenum type)
{
    return new QueryGL(type);
}

FenceNVImpl *RendererGL::createFenceNV()
{
    return new FenceNVGL();
}

FenceSyncImpl *RendererGL::createFenceSync()
{
    return new FenceSyncGL();
}

TransformFeedbackImpl *RendererGL::createTransformFeedback()
{
    return new TransformFeedbackGL();
}

void RendererGL::notifyDeviceLost()
{
    UNIMPLEMENTED();
}

bool RendererGL::isDeviceLost() const
{
    UNIMPLEMENTED();
    return bool();
}

bool RendererGL::testDeviceLost()
{
    UNIMPLEMENTED();
    return bool();
}

bool RendererGL::testDeviceResettable()
{
    UNIMPLEMENTED();
    return bool();
}

VendorID RendererGL::getVendorId() const
{
    UNIMPLEMENTED();
    return VendorID();
}

std::string RendererGL::getVendorString() const
{
    UNIMPLEMENTED();
    return std::string();
}

std::string RendererGL::getRendererDescription() const
{
    //UNIMPLEMENTED();
    return std::string();
}

void RendererGL::generateCaps(gl::Caps *outCaps, gl::TextureCapsMap* outTextureCaps, gl::Extensions *outExtensions) const
{
    nativegl_gl::GenerateCaps(mFunctions, outCaps, outTextureCaps, outExtensions);
}

Workarounds RendererGL::generateWorkarounds() const
{
    Workarounds workarounds;
    return workarounds;
}

}
