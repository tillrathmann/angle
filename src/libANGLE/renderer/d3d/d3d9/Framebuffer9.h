//
// Copyright 2014 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// Framebuffer9.h: Defines the Framebuffer9 class.

#ifndef LIBANGLE_RENDERER_D3D_D3D9_FRAMBUFFER9_H_
#define LIBANGLE_RENDERER_D3D_D3D9_FRAMBUFFER9_H_

#include "libANGLE/renderer/RenderTargetCache.h"
#include "libANGLE/renderer/d3d/FramebufferD3D.h"
#include "libANGLE/renderer/d3d/d3d9/renderer9_utils.h"

namespace rx
{
class Renderer9;

class Framebuffer9 : public FramebufferD3D
{
  public:
    Framebuffer9(const gl::FramebufferState &data, Renderer9 *renderer);
    ~Framebuffer9() override;

    gl::Error discard(const gl::Context *context, size_t count, const GLenum *attachments) override;
    gl::Error invalidate(const gl::Context *context,
                         size_t count,
                         const GLenum *attachments) override;
    gl::Error invalidateSub(const gl::Context *context,
                            size_t count,
                            const GLenum *attachments,
                            const gl::Rectangle &area) override;

    gl::Error getSamplePosition(const gl::Context *context,
                                size_t index,
                                GLfloat *xy) const override;

    gl::Error syncState(const gl::Context *context,
                        const gl::Framebuffer::DirtyBits &dirtyBits) override;

    const gl::AttachmentArray<RenderTarget9 *> &getCachedColorRenderTargets() const
    {
        return mRenderTargetCache.getColors();
    }

    const RenderTarget9 *getCachedDepthStencilRenderTarget() const
    {
        return mRenderTargetCache.getDepthStencil();
    }

  private:
    angle::Result clearImpl(const gl::Context *context,
                            const ClearParameters &clearParams) override;

    angle::Result readPixelsImpl(const gl::Context *context,
                                 const gl::Rectangle &area,
                                 GLenum format,
                                 GLenum type,
                                 size_t outputPitch,
                                 const gl::PixelPackState &pack,
                                 uint8_t *pixels) override;

    angle::Result blitImpl(const gl::Context *context,
                           const gl::Rectangle &sourceArea,
                           const gl::Rectangle &destArea,
                           const gl::Rectangle *scissor,
                           bool blitRenderTarget,
                           bool blitDepth,
                           bool blitStencil,
                           GLenum filter,
                           const gl::Framebuffer *sourceFramebuffer) override;

    GLenum getRenderTargetImplementationFormat(RenderTargetD3D *renderTarget) const override;

    Renderer9 *const mRenderer;

    RenderTargetCache<RenderTarget9> mRenderTargetCache;
};

}  // namespace rx

#endif // LIBANGLE_RENDERER_D3D_D3D9_FRAMBUFFER9_H_
