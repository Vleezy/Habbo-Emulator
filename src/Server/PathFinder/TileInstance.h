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

#ifndef _PATHFINDER_TILE_INSTANCE_h
#define _PATHFINDER_TILE_INSTANCE_h
#include "Common/SharedDefines.h"
#include "ItemManager.h"
#endif /* _PATHFINDER_TILE_INSTANCE_h */

namespace SteerStone
{
    class Habbo;
    
    /// This class is responsible for holding dynamic objects on the grid
    class TileInstance
    {
    public:
        friend class Room;

    public:
        /// Constructor
        TileInstance(int16 const p_X, int16 const p_Y);

        /// Deconstructor
        ~TileInstance();

    public:
        /// AddItem
        /// @p_Item : Item being added to tile
        void AddItem(Item* p_Item);

        /// GetItem
        Item* GetItem();

        /// GetTileState
        /// Returns current tile state
        int16 GetTileState() const;

        /// GetTileHeight
        /// Returns max tile height
        int16 GetTileHeight() const;

        /// SetTileOccupied
        /// Set the tile is being used by another habbo or object
        /// @p_Occupied : Set tile is being occupied or not
        /// @p_Habbo : Habbo user being added to the tile
        void SetTileOccupied(bool p_Occupied, Habbo* p_Habbo = nullptr);

        /// CanWalkOnTile
        /// Can Habbo walk on tile
        bool CanWalkOnTile();

        /// TileContainsSolidObject
        /// If tile contains a solid object
        bool TileContainsSolidObject();

        int16 GetTilePositionX() const { return m_TileX; }
        int16 GetTilePositionY() const { return m_TileY; }

    private:
        Item* m_Item;
        int16 m_TileState;              ///< Whether the tile is closed or open to use
        int16 m_TileHeight;             ///< Max height of the tile
        boost::optional<Habbo*> m_Habbo;///< Active user on tile

        int16 m_TileX;                  ///< Tile instance X Position
        int16 m_TileY;                  ///< ///< Tile instance X Position

        std::mutex m_Mutex;
    };

} ///< NAMESPACE STEERSTONE