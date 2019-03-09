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

#ifndef _Quad_Room_h_
#define _Quad_Room_h_
#include "Common/SharedDefines.h"
namespace Quad
{
    class Player;

    class Room
    {
    public:
        friend class RoomManager;

    public:
        Room();
        ~Room();

    public:
        uint32 GetId() const;
        std::string GetName() const;
        std::string GetPassword() const;
        std::string GetOwnerName() const;
        std::string GetFloorLevel() const;
        std::string GetModel() const;
        bool GetType() const;
        bool IsEnabled() const;
        bool IsShowOwnerName() const;
        bool IsSuperUser() const;
        uint32 GetCurrentIn() const;
        uint32 GetNowIn() const;
        uint32 GetMaxIn() const;

        void AddPlayer(std::shared_ptr<Player> player);
        void RemovePlayer(std::shared_ptr<Player> player);
        
    private:
        uint32 mId;
        std::string mName;
        std::string mDescription;
        std::string mPassword;
        std::string mOwnerName;
        std::string mFloorLevel;
        std::string mModel;
        bool mType;
        bool mEnabled;
        bool mShowOwnerName;
        bool mSuperUser;
        uint32 mCurrentIn;
        uint32 mNowIn;
        uint32 mMaxIn;

        std::vector<std::shared_ptr<Player>> mPlayers;
    };
}


#endif /* _Quad_Room_h_ */