/**
 ** gnome_shp_thumbnailer.cc - Create thumbnails for shp files in Nautilus.
 **
 ** Written: 2/14/2010 - Marzo, with lots of code borrowed from ipack and from
 ** the Gimp plugin.
 **/

/*
 *  Copyright (C) 2010-2022  The Exult Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifdef HAVE_CONFIG_H
#	include <config.h>
#endif

#ifdef __GNUC__
#	pragma GCC diagnostic push
#	pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#	pragma GCC diagnostic ignored "-Wold-style-cast"
#	if !defined(__llvm__) && !defined(__clang__)
#		pragma GCC diagnostic ignored "-Wuseless-cast"
#	else
#		pragma GCC diagnostic ignored "-Wzero-as-null-pointer-constant"
#		if __clang_major__ >= 16
#			pragma GCC diagnostic ignored "-Wcast-function-type-strict"
#		endif
#	endif
#endif    // __GNUC__
#include <gdk-pixbuf/gdk-pixbuf.h>
#ifdef __GNUC__
#	pragma GCC diagnostic pop
#endif    // __GNUC__

#include "exceptions.h"
#include "ibuf8.h"
#include "ignore_unused_variable_warning.h"
#include "pngio.h"
#include "utils.h"
#include "vgafile.h"

#include <array>
#include <iostream>

using namespace std;

// From Gimp plug-in. We use this single palette because the thumbnailer
// is meant to run unattended.
// TODO: Maybe expand to RGBA and use translucent colors instead of the
// more "normal" cycling colors. This causes to some thumbnails to look
// better, but others to look worse; most shapes are unaffected.
// The values used for the OpenGL translucent pixels in shapeid.cc (also
// in the blends.dat files for BG and SI) could be used for this purpose.
using U7Palette                         = std::array<unsigned char, 768>;
constexpr static const U7Palette shppal = {
		0x00, 0x00, 0x00, 0xF8, 0xF0, 0xCC, 0xF4, 0xE4, 0xA4, 0xF0, 0xDC, 0x78,
		0xEC, 0xD0, 0x50, 0xEC, 0xC8, 0x28, 0xD8, 0xAC, 0x20, 0xC4, 0x94, 0x18,
		0xB0, 0x80, 0x10, 0x9C, 0x68, 0x0C, 0x88, 0x54, 0x08, 0x74, 0x44, 0x04,
		0x60, 0x30, 0x00, 0x4C, 0x24, 0x00, 0x38, 0x14, 0x00, 0xF8, 0xFC, 0xFC,
		0xFC, 0xD8, 0xD8, 0xFC, 0xB8, 0xB8, 0xFC, 0x98, 0x9C, 0xFC, 0x78, 0x80,
		0xFC, 0x58, 0x64, 0xFC, 0x38, 0x4C, 0xFC, 0x1C, 0x34, 0xDC, 0x14, 0x28,
		0xC0, 0x0C, 0x1C, 0xA4, 0x08, 0x14, 0x88, 0x04, 0x0C, 0x6C, 0x00, 0x04,
		0x50, 0x00, 0x00, 0x34, 0x00, 0x00, 0x18, 0x00, 0x00, 0xFC, 0xEC, 0xD8,
		0xFC, 0xDC, 0xB8, 0xFC, 0xCC, 0x98, 0xFC, 0xBC, 0x7C, 0xFC, 0xAC, 0x5C,
		0xFC, 0x9C, 0x3C, 0xFC, 0x8C, 0x1C, 0xFC, 0x7C, 0x00, 0xE0, 0x6C, 0x00,
		0xC0, 0x60, 0x00, 0xA4, 0x50, 0x00, 0x88, 0x44, 0x00, 0x6C, 0x34, 0x00,
		0x50, 0x24, 0x00, 0x34, 0x18, 0x00, 0x18, 0x08, 0x00, 0xFC, 0xFC, 0xD8,
		0xF4, 0xF4, 0x9C, 0xEC, 0xEC, 0x60, 0xE4, 0xE4, 0x2C, 0xDC, 0xDC, 0x00,
		0xC0, 0xC0, 0x00, 0xA4, 0xA4, 0x00, 0x88, 0x88, 0x00, 0x6C, 0x6C, 0x00,
		0x50, 0x50, 0x00, 0x34, 0x34, 0x00, 0x18, 0x18, 0x00, 0xD8, 0xFC, 0xD8,
		0xB0, 0xFC, 0xAC, 0x8C, 0xFC, 0x80, 0x6C, 0xFC, 0x54, 0x50, 0xFC, 0x28,
		0x38, 0xFC, 0x00, 0x28, 0xDC, 0x00, 0x1C, 0xC0, 0x00, 0x14, 0xA4, 0x00,
		0x0C, 0x88, 0x00, 0x04, 0x6C, 0x00, 0x00, 0x50, 0x00, 0x00, 0x34, 0x00,
		0x00, 0x18, 0x00, 0xD4, 0xD8, 0xFC, 0xB8, 0xB8, 0xFC, 0x98, 0x98, 0xFC,
		0x7C, 0x7C, 0xFC, 0x5C, 0x5C, 0xFC, 0x3C, 0x3C, 0xFC, 0x00, 0x00, 0xFC,
		0x00, 0x00, 0xE0, 0x00, 0x00, 0xC0, 0x00, 0x00, 0xA4, 0x00, 0x00, 0x88,
		0x00, 0x00, 0x6C, 0x00, 0x00, 0x50, 0x00, 0x00, 0x34, 0x00, 0x00, 0x18,
		0xE8, 0xC8, 0xE8, 0xD4, 0x98, 0xD4, 0xC4, 0x6C, 0xC4, 0xB0, 0x48, 0xB0,
		0xA0, 0x28, 0xA0, 0x8C, 0x10, 0x8C, 0x7C, 0x00, 0x7C, 0x6C, 0x00, 0x6C,
		0x60, 0x00, 0x60, 0x50, 0x00, 0x50, 0x44, 0x00, 0x44, 0x34, 0x00, 0x34,
		0x24, 0x00, 0x24, 0x18, 0x00, 0x18, 0xF4, 0xE8, 0xE4, 0xEC, 0xDC, 0xD4,
		0xE4, 0xCC, 0xC0, 0xE0, 0xC0, 0xB0, 0xD8, 0xB0, 0xA0, 0xD0, 0xA4, 0x90,
		0xC8, 0x98, 0x80, 0xC4, 0x8C, 0x74, 0xAC, 0x7C, 0x64, 0x98, 0x6C, 0x58,
		0x80, 0x5C, 0x4C, 0x6C, 0x4C, 0x3C, 0x54, 0x3C, 0x30, 0x3C, 0x2C, 0x24,
		0x28, 0x1C, 0x14, 0x10, 0x0C, 0x08, 0xEC, 0xEC, 0xEC, 0xDC, 0xDC, 0xDC,
		0xCC, 0xCC, 0xCC, 0xBC, 0xBC, 0xBC, 0xAC, 0xAC, 0xAC, 0x9C, 0x9C, 0x9C,
		0x8C, 0x8C, 0x8C, 0x7C, 0x7C, 0x7C, 0x6C, 0x6C, 0x6C, 0x60, 0x60, 0x60,
		0x50, 0x50, 0x50, 0x44, 0x44, 0x44, 0x34, 0x34, 0x34, 0x24, 0x24, 0x24,
		0x18, 0x18, 0x18, 0x08, 0x08, 0x08, 0xE8, 0xE0, 0xD4, 0xD8, 0xC8, 0xB0,
		0xC8, 0xB0, 0x90, 0xB8, 0x98, 0x70, 0xA8, 0x84, 0x58, 0x98, 0x70, 0x40,
		0x88, 0x5C, 0x2C, 0x7C, 0x4C, 0x18, 0x6C, 0x3C, 0x0C, 0x5C, 0x34, 0x0C,
		0x4C, 0x2C, 0x0C, 0x3C, 0x24, 0x0C, 0x2C, 0x1C, 0x08, 0x20, 0x14, 0x08,
		0xEC, 0xE8, 0xE4, 0xDC, 0xD4, 0xD0, 0xCC, 0xC4, 0xBC, 0xBC, 0xB0, 0xAC,
		0xAC, 0xA0, 0x98, 0x9C, 0x90, 0x88, 0x8C, 0x80, 0x78, 0x7C, 0x70, 0x68,
		0x6C, 0x60, 0x5C, 0x60, 0x54, 0x50, 0x50, 0x48, 0x44, 0x44, 0x3C, 0x38,
		0x34, 0x30, 0x2C, 0x24, 0x20, 0x20, 0x18, 0x14, 0x14, 0xE0, 0xE8, 0xD4,
		0xC8, 0xD4, 0xB4, 0xB4, 0xC0, 0x98, 0x9C, 0xAC, 0x7C, 0x88, 0x98, 0x60,
		0x70, 0x84, 0x4C, 0x5C, 0x70, 0x38, 0x4C, 0x5C, 0x28, 0x40, 0x50, 0x20,
		0x38, 0x44, 0x1C, 0x30, 0x3C, 0x18, 0x28, 0x30, 0x14, 0x20, 0x24, 0x10,
		0x18, 0x1C, 0x08, 0x0C, 0x10, 0x04, 0xEC, 0xD8, 0xCC, 0xDC, 0xB8, 0xA0,
		0xCC, 0x98, 0x7C, 0xBC, 0x80, 0x5C, 0xAC, 0x64, 0x3C, 0x9C, 0x50, 0x24,
		0x8C, 0x3C, 0x0C, 0x7C, 0x2C, 0x00, 0x6C, 0x24, 0x00, 0x60, 0x20, 0x00,
		0x50, 0x1C, 0x00, 0x44, 0x14, 0x00, 0x34, 0x10, 0x00, 0x24, 0x0C, 0x00,
		0xF0, 0xF0, 0xFC, 0xE4, 0xE4, 0xFC, 0xD8, 0xD8, 0xFC, 0xCC, 0xCC, 0xFC,
		0xC0, 0xC0, 0xFC, 0xB4, 0xB4, 0xFC, 0xA8, 0xA8, 0xFC, 0x9C, 0x9C, 0xFC,
		0x84, 0xD0, 0x00, 0x84, 0xB0, 0x00, 0x7C, 0x94, 0x00, 0x68, 0x78, 0x00,
		0x50, 0x58, 0x00, 0x3C, 0x40, 0x00, 0x2C, 0x24, 0x00, 0x1C, 0x08, 0x00,
		0x20, 0x00, 0x00, 0xEC, 0xD8, 0xC4, 0xDC, 0xC0, 0xB4, 0xCC, 0xB4, 0xA0,
		0xBC, 0x9C, 0x94, 0xAC, 0x90, 0x80, 0x9C, 0x84, 0x74, 0x8C, 0x74, 0x64,
		0x7C, 0x64, 0x58, 0x6C, 0x54, 0x4C, 0x60, 0x48, 0x44, 0x50, 0x40, 0x38,
		0x44, 0x34, 0x2C, 0x34, 0x2C, 0x24, 0x24, 0x18, 0x18, 0x18, 0x10, 0x10,
		0xFC, 0xF8, 0xFC, 0xAC, 0xD4, 0xF0, 0x70, 0xAC, 0xE4, 0x34, 0x8C, 0xD8,
		0x00, 0x6C, 0xD0, 0x30, 0x8C, 0xD8, 0x6C, 0xB0, 0xE4, 0xB0, 0xD4, 0xF0,
		0xFC, 0xFC, 0xF8, 0xFC, 0xEC, 0x40, 0xFC, 0xC0, 0x28, 0xFC, 0x8C, 0x10,
		0xFC, 0x50, 0x00, 0xC8, 0x38, 0x00, 0x98, 0x28, 0x00, 0x68, 0x18, 0x00,
		0x7C, 0xDC, 0x7C, 0x44, 0xB4, 0x44, 0x18, 0x90, 0x18, 0x00, 0x6C, 0x00,
		0xF8, 0xB8, 0xFC, 0xFC, 0x64, 0xEC, 0xFC, 0x00, 0xB4, 0xCC, 0x00, 0x70,
		0xFC, 0xFC, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFC, 0x00, 0xFC, 0x00, 0x00,
		0xFC, 0xFC, 0xFC, 0x61, 0x61, 0x61, 0xC0, 0xC0, 0xC0, 0xFC, 0x00, 0xF1};

// Finds the integer square root of a positive number
unsigned intSqrt(unsigned remainder) {
	unsigned place = 1U << (sizeof(unsigned) * 8
							- 2);    // calculated by precompiler = same runtime
									 // as: place = 0x40000000
	while (place > remainder) {
		place /= 4;    // optimized by complier as place >>= 2
	}

	unsigned root = 0;
	while (place) {
		if (remainder >= root + place) {
			remainder -= root + place;
			root += place * 2;
		}
		root /= 2;
		place /= 4;
	}
	return root;
}

const unsigned char transp = 255;    // Transparent pixel.

static unsigned char* Convert8to32(
		const unsigned char* bits, size_t nsize, const U7Palette& palette) {
	auto* out = new unsigned char[nsize * 4];
	for (size_t i = 0; i < nsize; i++) {
		const size_t pix = bits[i];
		out[4 * i]       = palette[3 * pix];
		out[4 * i + 1]   = palette[3 * pix + 1];
		out[4 * i + 2]   = palette[3 * pix + 2];
		out[4 * i + 3]   = pix == transp ? 0 : 255;
	}
	return out;
}

/*
 *  Single frame renderer.
 */
struct Render_frame {
	void operator()(
			Image_buffer8& img, Shape_frame& frame, int w, int h, int xo,
			int yo) {
		ignore_unused_variable_warning(w, h);
		frame.paint(&img, xo + frame.get_xleft(), yo + frame.get_yabove());
	}
};

/*
 *  Shape tile renderer.
 */
struct Render_tiles {
	void operator()(
			Image_buffer8& img, Shape& shape, int w, int h, int xo, int yo) {
		ignore_unused_variable_warning(h);
		const int dim0_cnt = w / 8;
		int       f        = -1;
		for (auto& frame : shape) {
			f++;
			if (!frame) {
				continue;    // We'll just leave empty ones blank.
			}
			if (frame->is_rle() || frame->get_width() != 8
				|| frame->get_height() != 8) {
				cerr << "Can only tile 8x8 flat shapes, but shape doesn't "
						"qualify"
					 << endl;
				exit(4);
			}
			const int x = f % dim0_cnt;
			const int y = f / dim0_cnt;
			frame->paint(
					&img, xo + x * 8 + frame->get_xleft(),
					yo + y * 8 + frame->get_yabove());
		}
	}
};

/*
 *  Write out the desired data as a .png. Yes, this is overkill :-)
 */

template <typename Data, typename Render>
static void Write_thumbnail(
		char*            filename,    // Base filename to write.
		Data&            data,        // What to write.
		const U7Palette& palette,     // 3*256 bytes.
		int w, int h,                 // Width, height of rendered image.
		int size                      // Desired thumbnail size
) {
	cout << "Writing " << filename << endl;
	// Make into a padded square of the largest dimension, but limit it
	// to a minimum of 16x16 to avoid blurring.
	const int     w1 = std::max(std::max(w, h), 16);
	const int     h1 = w1;
	Image_buffer8 img(w1, h1);    // Render into a buffer.
	img.fill8(transp);            // Fill with transparent pixel.
	Render r;
	r(img, data, w, h, (w1 - w) / 2, (h1 - h) / 2);
	unsigned char* bits = Convert8to32(img.get_bits(), w1 * h1, palette);
	if (w1 != size) {
		GdkPixbuf* pixbuf = gdk_pixbuf_new_from_data(
				bits, GDK_COLORSPACE_RGB, true, 8, w1, h1, 4 * w1, nullptr,
				nullptr);
		GdkPixbuf* smallpixbuf
				= gdk_pixbuf_scale_simple(pixbuf, size, size, GDK_INTERP_HYPER);
		// Write out to the .png.
		if (!Export_png32(
					filename, size, size, 4 * size, 0, 0,
					gdk_pixbuf_get_pixels(smallpixbuf))) {
			throw file_write_exception(filename);
		}
		g_object_unref(smallpixbuf);
		g_object_unref(pixbuf);
	}
	// Write out to the .png.
	else if (!Export_png32(filename, w1, h1, 4 * w1, 0, 0, bits)) {
		throw file_write_exception(filename);
	}
	delete[] bits;
}

int main(int argc, char* argv[]) {
	if (argc < 5) {
		cerr << "Usage: gnome-shp-thumbnailer -s size inputfile outputfile"
			 << endl;
		return 1;
	}
	const int size = atoi(argv[2]);
	if (size < 0 || size > 2048) {
		cerr << "Invalid thumbnail size: " << size << "!" << endl;
		return 2;
	}
	char*      inputfile  = argv[3];
	char*      outputfile = argv[4];
	Shape_file shape(inputfile);    // May throw an exception.
	if (shape.is_empty()) {
		cerr << "Shape is empty!" << endl;
		return 3;
	}
	try {
		if (shape.is_rle()) {
			for (auto& frame : shape) {
				if (!frame || frame->is_empty()) {
					continue;
				}
				Write_thumbnail<Shape_frame, Render_frame>(
						outputfile, *frame, shppal, frame->get_width(),
						frame->get_height(), size);
				break;
			}
		} else {
			const unsigned nframes = shape.get_num_frames();
			unsigned       dim0    = intSqrt(nframes);
			if (dim0 * dim0 < nframes) {
				dim0 += 1;
			}
			const unsigned dim1 = (nframes + dim0 - 1) / dim0;
			Write_thumbnail<Shape, Render_tiles>(
					outputfile, shape, shppal, dim0 * 8, dim1 * 8, size);
		}
	} catch (const std::exception& except) {
		cerr << "Could not generate thumbnail: " << except.what() << endl;
		return 4;
	}
	return 0;
}
