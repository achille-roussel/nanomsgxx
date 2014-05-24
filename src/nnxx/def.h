/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 Achille Roussel <achille.roussel@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef NNXX_DEF_H
#define NNXX_DEF_H

// Define dummy version of NNXX_EXPORT for platforms that don't support any of
// __declspec or __attribute__
#define NNXX_EXPORT

#if NNXX_HAS_DECLSPEC
#undef  NNXX_EXPORT
#define NNXX_EXPORT __declspec(dllexport)
#endif // NNXX_HAS_DECLSPEC

#if NNXX_HAS_ATTRIBUTE_VISIBILITY
#undef  NNXX_EXPORT
#define NNXX_EXPORT __attribute__((visibility("default")))
#endif // NNXX_HAS_ATTRIBUTE_VISIBILITY

#endif // NNXX_DEF_H
