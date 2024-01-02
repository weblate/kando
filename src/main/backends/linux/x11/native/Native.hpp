//////////////////////////////////////////////////////////////////////////////////////////
//   _  _ ____ _  _ ___  ____                                                           //
//   |_/  |__| |\ | |  \ |  |    This file belongs to Kando, the cross-platform         //
//   | \_ |  | | \| |__/ |__|    pie menu. Read more on github.com/kando-menu/kando     //
//                                                                                      //
//////////////////////////////////////////////////////////////////////////////////////////

// SPDX-FileCopyrightText: Simon Schneegans <code@simonschneegans.de>
// SPDX-License-Identifier: MIT

#ifndef NATIVE_HPP
#define NATIVE_HPP

#include <napi.h>

/**
 * This class allows moving the mouse pointer and simulating key presses on Wayland. For
 * this, it uses the virtual-pointer and virtual-keyboard protocols. See index.ts for more
 * information regarding the exposed functions.
 *
 * The sending of key events is a little bit more complicated than I would like it to be.
 * As far as I understand, the virtual-keyboard protocol requires that the client (we)
 * keeps track of the current modifier state. This means, we have to somehow check which
 * scan codes map to which modifier keys and keep track of which modifiers are currently
 * pressed. This is done using the xkbcommon library using the keymap we can get from the
 * real keyboard.
 */
class Native : public Napi::Addon<Native> {
 public:
  Native(Napi::Env env, Napi::Object exports);

 private:
  /**
   * This function is called when the movePointer function is called from JavaScript. It
   * expects two numbers which are used for the relative movement of the pointer.
   * If something goes wrong, it throws a JavaScript exception.
   *
   * @param info The arguments passed to the movePointer function. It should contain two
   *             numbers.
   */
  void movePointer(const Napi::CallbackInfo& info);

  /**
   * This function is called when the simulateKey function is called from JavaScript. It
   * expects a number which is used as the scan code of the key to be pressed and a
   * boolean which indicates whether the key should be pressed or released.
   * If something goes wrong, it throws a JavaScript exception.
   *
   * @param info The arguments passed to the simulateKey function. It should contain a
   *             number and a boolean.
   */
  void simulateKey(const Napi::CallbackInfo& info);

  /**
   * This function is called when the getActiveWindow function is called from JavaScript.
   * It returns the app and class of the currently active window.
   *
   * @param info The arguments passed to the getActiveWindow function. It should contain
   *            no arguments.
   */
  Napi::Value getActiveWindow(const Napi::CallbackInfo& info);
};

#endif // NATIVE_HPP