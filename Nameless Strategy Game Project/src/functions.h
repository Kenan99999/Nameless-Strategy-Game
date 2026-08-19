#pragma once

void CreateTerrains();

void Saves();

void CreateMapBonds();

void ClearTroops();

void GetMouseCoords();

void IncreaseWarPoints();

void Combat();

void ClearMouseCoords();

void TileCenterSelector();

bool IsCommanderPlacementOkay(int Tile, int PlayerID);

void LoadGameTextures();

bool IsPlacementOkay(int Tile, int PlayerID);

bool AddBoughtTroopToTheTroopBank(int Troop, int PlayerID);

void DeleteEliminatedTroops(int PlayerCount);