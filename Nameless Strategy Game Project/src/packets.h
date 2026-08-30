#pragma once
enum Packets {
    DENY = 0,
    SUCCESS = 1,
    BUY_TROOP = 2,
    PLACE_TROOP = 3,
    MOVE_TROOP = 4,
    DELETE_TROOP = 5,
    BUILD = 6,
    PLACE_COMMANDER = 7,
    JOIN_RESPONSE = 8,
    START_GAME = 9,
    DISCONNECTED = 10,
    INCREASE_ROUND = 11,
    COMBAT = 12,
    LOAD = 13
};

struct PACKET_PLAYER_JOIN {
    Packets type = JOIN_RESPONSE;
    int ID;
    int CurrentPlayerCount;
};

struct PACKET_START_THE_GAME {
    Packets type = START_GAME;
};

struct PACKET_PLAYER_DISCONNECT {
    Packets type = DISCONNECTED;
    int DisconnectedID;
};

struct PACKET_COMMANDER_PLACEMENT {
    Packets type = PLACE_COMMANDER;
    int PlayerID;
    int Tile;
};

struct PACKET_BUY_TROOP {
    Packets type = BUY_TROOP;
    int PlayerID;
    int BoughtTroop;
};

struct PACKET_ROUND {
    Packets type = INCREASE_ROUND;
};

struct PACKET_PLACE_TROOP {
    Packets type = PLACE_TROOP;
    int Tile;
    int ID;
    int Slot;
    troop Troop;
};

struct PACKET_MOVE_TROOP {
    Packets type = MOVE_TROOP;
    int FromTile;
    int ToTile;
    pair<int, troop> Moving[5];
    int ID;
};

struct PACKET_COMBAT {
    Packets type = COMBAT;
    pair<pair<int, int>, int> NewTroopHealths[300];
    bool CommanderAvalibility[6];
    int index;
};

struct PACKET_DELETE_TROOP {
    Packets type = DELETE_TROOP;
    int Tile;
    int ID;
    int Slot;
    int NewWarPoints;
};

struct PACKET_BUILD {
    Packets type = BUILD;
    int Tile;
    int Who;
    int ID;
    int Slot;
    building Built;
};

struct PACKET_SYNC_THE_GAME {
    Packets type = LOAD;
    troop Troops[47][10];
    building Buildings[47][10];
    int Round;
    int WarPoints[6];
    troop TroopBanks[6][10];
    bool Commanders[6];
};