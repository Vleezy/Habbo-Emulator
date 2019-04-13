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

#pragma once
#include "Common/SharedDefines.h"
#include "HabboSocket.h"

namespace SteerStone
{
    enum ConnectionError
    {
        ROOM_IS_FULL                = 1,
        ROOM_IS_CLOSED              = 2,
        ROOM_IS_IN_QUEUE            = 3
    };

    namespace HabboPacket
    {
        namespace Navigator
        {
            /// SERVER_CANT_CONNECT packet builder
            class CantConnect final : public ServerPacket
            {
            public:
                /// Constructor 
                CantConnect() : ServerPacket(SERVER_CANT_CONNECT) {}

            public:
                /// Write the packet
                StringBuffer const* Write();

                ConnectionError ErrorCode;
            };

            /// SERVER_FAVOURITE_ROOMS_RESULT packet builder
            class FavouriteRoomResult final : public ServerPacket
            {
            public:
                /// Constructor 
                FavouriteRoomResult() : ServerPacket(SERVER_FAVOURITE_ROOMS_RESULT) {}

            public:
                /// Write the packet
                StringBuffer const* Write();
            };

        } ///< NAMESPACE NAVIGATOR
    } ///< NAMESPACE HABBOPACKET
} ///< NAMESPACE STEERSTONE