#pragma once

void CreateTerrains();

void Saves();

void CreateMapBonds();

void ClearTroops();

void GetMouseCoords();

void IncreaseWarPoints();

void Combat(int PlayerCurrent);

void ClearMouseCoords();

void TileCenterSelector();

bool IsCommanderPlacementOkay(int Tile, int PlayerID);

void LoadGameTextures();

bool IsPlacementOkay(int Tile, int PlayerID);

bool AddBoughtTroopToTheTroopBank(int Troop, int PlayerID);

void DeleteEliminatedTroops(int PlayerCount);

bool IsMovingOkay(int FromTileSelected, int ToTileSelected, int PlayerID);

void DeleteEliminatedTroops();

bool DeleteTheTroop(int PlayerID, int Tile, int Slot);

bool IsBuildOkay(int, PlayerID, int Slot);