/* bzflag
 * Copyright (c) 1993-2020 Tim Riker
 *
 * This package is free software;  you can redistribute it and/or
 * modify it under the terms of the license found in the file
 * named COPYING that should have accompanied this file.
 *
 * THIS PACKAGE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

/* bzflag special common - 1st one */
#include "common.h"

#include <iostream>
#include <string>
#include <list>
#include "WorldEventManager.h"

std::map<bz_Plugin*,bz_EventHandler*> HandlerMap;

std::list<bz_eEventType> callingEventStack;


//-------------------WorldEventManager--------------------
WorldEventManager::WorldEventManager()
{
    if (callingEventStack.size() > 0)
        callingEventStack.clear();
}

WorldEventManager::~WorldEventManager()
{
    tvEventList::iterator eventItr = eventList.begin();
    while (eventItr != eventList.end())
        delete (*eventItr++);

    eventList.clear();
}

void WorldEventManager::addEvent ( bz_eEventType eventType, bz_EventHandler* theEvent )
{
    if (!theEvent)
        return;

    theEvent->AddEvent(eventType);

    if (callingEventStack.size() > 0 && callingEventStack.back() == eventType)
        pendingAdds.push_back(theEvent);
    else
    {
        if (std::find(eventList.begin(),eventList.end(),theEvent) == eventList.end())
            eventList.push_back(theEvent);
    }
}

void WorldEventManager::removeEvent ( bz_eEventType eventType, bz_EventHandler* theEvent )
{
    if (!theEvent)
        return;

    theEvent->RemoveEvent(eventType);
}

bool WorldEventManager::removeHandler(bz_EventHandler* theEvent)
{
    if (callingEventStack.size() > 0)
    {
        pendingRemovals.push_back(theEvent);
        return std::find(eventList.begin(),eventList.end(),theEvent) != eventList.end();
    }

    tvEventList::iterator itr = std::find(eventList.begin(),eventList.end(),theEvent);
    if (itr != eventList.end())
    {
        eventList.erase(itr);
        return true;
    }

    return false;
}

void WorldEventManager::callEvents ( bz_eEventType eventType, bz_EventData  *eventData )
{
    if (!eventData)
        return;
    callingEventStack.push_back(eventType);
    eventData->eventType = eventType;

//  tvEventList::iterator itr = eventList.begin();
//  while (itr != eventList.end())
    for (size_t i = 0; i < eventList.size(); i++)
    {
        if (eventList[i]->HasEvent(eventType))
            eventList[i]->process(eventData);
    }

    callingEventStack.pop_back();
    processPending();
}

void WorldEventManager::callEvents (  bz_EventData  *eventData )
{
    callEvents(eventData->eventType,eventData);
}

void WorldEventManager::processPending()
{
    for (size_t i = 0; i < pendingAdds.size(); i++)
    {
        if (std::find(eventList.begin(),eventList.end(),pendingAdds[i]) == eventList.end())
            eventList.push_back(pendingAdds[i]);
    }
    pendingAdds.clear();

    for (size_t i = 0; i < pendingRemovals.size(); i++)
        removeHandler(pendingRemovals[i]);

    pendingRemovals.clear();
}

bool RegisterEvent ( bz_eEventType eventType, bz_Plugin* plugin )
{
    if (!plugin)
        return false;

    bz_EventHandler *handler = NULL;

    if (HandlerMap.find(plugin) == HandlerMap.end())
    {
        handler = new bz_EventHandler();
        handler->plugin = plugin;
        HandlerMap[plugin] = handler;
    }
    else
        handler = HandlerMap[plugin];

    worldEventManager.addEvent(eventType,handler);
    return true;
}

bool RemoveEvent ( bz_eEventType eventType, bz_Plugin* plugin )
{
    if (!plugin || HandlerMap.find(plugin) == HandlerMap.end())
        return false;

    bz_EventHandler *handler = HandlerMap[plugin];
    worldEventManager.removeEvent(eventType,handler);

    if (handler->HandledEvents.empty())
        worldEventManager.removeHandler(handler);

    return true;
}

bool FlushEvents(bz_Plugin* plugin)
{
    if (!plugin || HandlerMap.find(plugin) == HandlerMap.end())
        return false;

    bz_EventHandler *handler = HandlerMap[plugin];
    worldEventManager.removeHandler(handler);

    return true;
}

// Local Variables: ***
// mode: C++ ***
// tab-width: 4 ***
// c-basic-offset: 4 ***
// indent-tabs-mode: nil ***
// End: ***
// ex: shiftwidth=4 tabstop=4
