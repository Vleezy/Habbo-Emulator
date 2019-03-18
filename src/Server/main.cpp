/*
* Liam Ashdown
* Copyright (C) 2019
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
//-----------------------------------------------//
#include "PlayerSocket.h"
#include "Network/Listener.h"
#include "Common/SharedDefines.h"
#include "Config/Config.h"
#include "Database/Database.h"
#include "World.h"
#include "Platform/Thread/ThreadPool.h"
#include "RoomManager.h"
#include "ItemManager.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include "Common/Timer.h"
//-----------------------------------------------//
bool LoadDatabase();
//-----------------------------------------------//
int main()
{
    // Initialize our logger
    static plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender;
    plog::init(plog::verbose, &consoleAppender);

    LOG_NONE << "   ____                  _ ______                 _       _             ";
    LOG_NONE << "  / __ \\                | |  ____|               | |     | |            ";
    LOG_NONE << " | |  | |_   _  __ _  __| | |__   _ __ ___  _   _| | __ _| |_ ___  _ __ ";
    LOG_NONE << " | |  | | | | |/ _` |/ _` |  __| | '_ ` _ \\| | | | |/ _` | __/ _ \\| '__|";
    LOG_NONE << " | |__| | |_| | (_| | (_| | |____| | | | | | |_| | | (_| | || (_) | |   ";
    LOG_NONE << "  \\____\\_\\__,_|\\__,_|\\__,_|______|_| |_| |_|\\__,_|_|\\__,_|\\__\\___/|_|   ";
    LOG_NONE << "                                             Powered by Boost & MySQL";


    if (!sConfig->SetFile("server.conf"))
    {
        LOG_ERROR << "Could not find server.conf";
        Sleep(5000);
        return 1;
    }

    if (!LoadDatabase())
    {
        Sleep(5000);
        return -1;
    }

    sOpcode->InitializePackets();
    sRoomMgr->LoadRooms();
    sRoomMgr->LoadRoomCategories();
    sRoomMgr->LoadFavouriteRooms();
    sRoomMgr->LoadRoomModels();


    Quad::Listener<Quad::PlayerSocket> listener(sConfig->GetStringDefault("BindIP", "127.0.0.1"), sConfig->GetIntDefault("ServerPort", DEFAULT_SERVER_PORT),
        sConfig->GetIntDefault("NetworkThreadProcessors", 1));

    LOG_INFO << "Successfully booted up QuadEmulator! Listening on " << sConfig->GetStringDefault("BindIP", "127.0.0.1") << " " << sConfig->GetIntDefault("ServerPort", DEFAULT_SERVER_PORT);

    Timer timer;
    while (!Quad::World::StopWorld())
    {
        sWorld->UpdateWorld();

        // Update the world every 500 ms
        if (timer.Elasped() < UPDATE_WORLD_TIMER)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds((uint32)(UPDATE_WORLD_TIMER - timer.Elasped())));
            timer.Reset();
        }
    }
   
    sWorld->CleanUp();

    return 0;
}
//-----------------------------------------------//
bool LoadDatabase()
{
    if (sDatabase->CreateDatabase(sConfig->GetStringDefault("UserDatabaseInfo").c_str(), sConfig->GetIntDefault("UserDatabaseInfo.WorkerThreads", 1)) &&
        sDatabase->CreateDatabase(sConfig->GetStringDefault("RoomDatabaseInfo").c_str(), sConfig->GetIntDefault("RoomDatabaseInfo.WorkerThreads", 1)))
        return true;
    else
        return false;
}