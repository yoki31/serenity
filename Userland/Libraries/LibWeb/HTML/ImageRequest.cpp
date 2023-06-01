/*
 * Copyright (c) 2023, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibGfx/Bitmap.h>
#include <LibWeb/Fetch/Infrastructure/FetchController.h>
#include <LibWeb/HTML/DecodedImageData.h>
#include <LibWeb/HTML/ImageRequest.h>

namespace Web::HTML {

ErrorOr<NonnullRefPtr<ImageRequest>> ImageRequest::create()
{
    return adopt_nonnull_ref_or_enomem(new (nothrow) ImageRequest);
}

ImageRequest::ImageRequest() = default;

ImageRequest::~ImageRequest() = default;

// https://html.spec.whatwg.org/multipage/images.html#img-available
bool ImageRequest::is_available() const
{
    // When an image request's state is either partially available or completely available, the image request is said to be available.
    return m_state == State::PartiallyAvailable || m_state == State::CompletelyAvailable;
}

ImageRequest::State ImageRequest::state() const
{
    return m_state;
}

void ImageRequest::set_state(State state)
{
    m_state = state;
}

AK::URL const& ImageRequest::current_url() const
{
    return m_current_url;
}

void ImageRequest::set_current_url(AK::URL url)
{
    m_current_url = move(url);
}

// https://html.spec.whatwg.org/multipage/images.html#abort-the-image-request
void ImageRequest::abort(JS::Realm& realm)
{
    // 1. Forget image request's image data, if any.
    m_image_data = nullptr;

    // 2. Abort any instance of the fetching algorithm for image request,
    //    discarding any pending tasks generated by that algorithm.
    if (m_fetch_controller)
        m_fetch_controller->abort(realm, {});

    m_fetch_controller = nullptr;
}

RefPtr<DecodedImageData const> ImageRequest::image_data() const
{
    return m_image_data;
}

void ImageRequest::set_image_data(RefPtr<DecodedImageData const> data)
{
    m_image_data = move(data);
}

// https://html.spec.whatwg.org/multipage/images.html#prepare-an-image-for-presentation
void ImageRequest::prepare_for_presentation(HTMLImageElement&)
{
    // FIXME: 1. Let exifTagMap be the EXIF tags obtained from req's image data, as defined by the relevant codec. [EXIF]
    // FIXME: 2. Let physicalWidth and physicalHeight be the width and height obtained from req's image data, as defined by the relevant codec.
    // FIXME: 3. Let dimX be the value of exifTagMap's tag 0xA002 (PixelXDimension).
    // FIXME: 4. Let dimY be the value of exifTagMap's tag 0xA003 (PixelYDimension).
    // FIXME: 5. Let resX be the value of exifTagMap's tag 0x011A (XResolution).
    // FIXME: 6. Let resY be the value of exifTagMap's tag 0x011B (YResolution).
    // FIXME: 7. Let resUnit be the value of exifTagMap's tag 0x0128 (ResolutionUnit).
    // FIXME: 8. If either dimX or dimY is not a positive integer, then return.
    // FIXME: 9. If either resX or resY is not a positive floating-point number, then return.
    // FIXME: 10. If resUnit is not equal to 2 (Inch), then return.
    // FIXME: 11. Let widthFromDensity be the value of physicalWidth, multiplied by 72 and divided by resX.
    // FIXME: 12. Let heightFromDensity be the value of physicalHeight, multiplied by 72 and divided by resY.
    // FIXME: 13. If widthFromDensity is not equal to dimX or heightFromDensity is not equal to dimY, then return.
    // FIXME: 14. If req's image data is CORS-cross-origin, then set img's intrinsic dimensions to dimX and dimY, scale img's pixel data accordingly, and return.
    // FIXME: 15. Set req's preferred density-corrected dimensions to a struct with its width set to dimX and its height set to dimY.
    // FIXME: 16. Update req's img element's presentation appropriately.
}

void ImageRequest::set_fetch_controller(JS::GCPtr<Fetch::Infrastructure::FetchController> fetch_controller)
{
    m_fetch_controller = move(fetch_controller);
}

}
