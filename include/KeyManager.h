/* bzflag
 * Copyright (c) 1993 - 2003 Tim Riker
 *
 * This package is free software;  you can redistribute it and/or
 * modify it under the terms of the license found in the file
 * named LICENSE that should have accompanied this file.
 *
 * THIS PACKAGE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

/*
 * keyboard mapping stuff
 */

#ifndef BZF_KEYMANAGER_H
#define BZF_KEYMANAGER_H

#include "common.h"
#include <string>
#include <map>
#include "BzfEvent.h"
#include "CallbackList.h"

#define KEYMGR (KeyManager::getInstance())

class KeyManager {
public:
  typedef void (*IterateCallback)(const std::string& name, bool press,
				  const std::string& cmd, void* userData);
  typedef IterateCallback ChangeCallback;

  KeyManager();
  ~KeyManager();

  // bind/unbind a command to/from a key event press or release
  void			bind(const BzfKeyEvent&,
			     bool press, const std::string& cmd);
  void			unbind(const BzfKeyEvent&, bool press);

  // get the command for a key event press or release
  std::string		get(const BzfKeyEvent&, bool press) const;

  // convert a key event to/from a string
  std::string		keyEventToString(const BzfKeyEvent&) const;
  bool			stringToKeyEvent(const std::string&, BzfKeyEvent&) const;

  // invoke callback for each bound key
  void			iterate(IterateCallback callback, void* userData);

  // add/remove a callback to invoke when a key binding is added,
  // removed, or changed.
  void			addCallback(ChangeCallback, void* userData);
  void			removeCallback(ChangeCallback, void* userData);

  static KeyManager*	getInstance();

private:
  void			notify(const BzfKeyEvent&,
			       bool press, const std::string& cmd);

  struct CallbackInfo {
  public:
    std::string		name;
    bool		press;
    std::string		cmd;
  };
  static bool		onCallback(ChangeCallback, void*, void*);

private:
  class KeyEventLess {
  public:
    bool		operator()(const BzfKeyEvent&,
				   const BzfKeyEvent&) const;
  };

  typedef std::map<BzfKeyEvent, std::string, KeyEventLess> EventToCommandMap;
  typedef std::map<std::string, BzfKeyEvent> StringToEventMap;

  EventToCommandMap	pressEventToCommand;
  EventToCommandMap	releaseEventToCommand;
  StringToEventMap	stringToEvent;
  CallbackList<ChangeCallback>	callbacks;
  static KeyManager*	instance;
  static const char*	buttonNames[];
  static const char*	asciiNames[][2];
};

// this is to be implemented within the requisite source file for the application using it.
// in BZFlag's case, it happens to be in bzflag.cxx
#define NUM_DEFAULT_BINDINGS	65
extern const char*		defaultBindings[NUM_DEFAULT_BINDINGS];

#endif // BZF_KEYMANAGER_H
// ex: shiftwidth=2 tabstop=8
