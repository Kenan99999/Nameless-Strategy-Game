#include "functions.h"
#include "globals.h"
#include <bits/stdc++.h>

using namespace std;
using namespace filesystem;

void CreateTerrains() { // Terrain mapi olmadığı için bunu elimle yapıyorum ilerde değiştirmek nasip olursa değiştiririm
    string LoadingFile = "centers/tiles.txt";
    ifstream File(LoadingFile);
    if(exists(LoadingFile)) {
        for(int i = 0; i < 47 /* TileCount*/; ++i) {
            int x;
            int y;
            File >> x;
            File >> y;
            Centers.push_back({x, y});
        }
    }
    string LoadingFile2 = "centers/terrain.txt";
    ifstream File2(LoadingFile2);
    if(exists(LoadingFile2)) {
        for(int i = 0; i < 47 /* TileCount*/; ++i) {
            File2 >> Terrain[i];
        }
    }
}

void Saves() {
    if(exists("saves")) {
        for(const auto& file : directory_iterator("saves")) {
            if(file.path().extension() == ".save") {
                if(find(GameSaves.begin(), GameSaves.end(), file.path().filename().string()) == GameSaves.end()) GameSaves.push_back(file.path().filename().string());
            }
        }
    }
}

void CreateMapBonds() {
    string LoadingFile = "centers/bonds.txt";
    ifstream File(LoadingFile);
    if(exists(LoadingFile)) {
        for(int i = 0; i < 47; ++i) {
            int count;
            int tile;
            File >> count;
            File >> tile;
            for(int j = 0; j < count; ++j) {
                int temp;
                File >> temp;
                Tiles[tile].push_back(temp);
            }
        }
    }
}

void ClearTroops() {
    for(int i = 0; i < 47; ++i) {
        for(int j = 0; j < 10; ++j) {
            Troops[i][j] = empty_troop;
        }
    }
    for(int i = 0; i < 10; ++i) {
        for(int j = 0; j < PlayerCount; ++j) {
            Players[j].TroopBank[i] = empty_troop;
        }
    }
    for(int i = 0; i < 47; ++i) {
        for(int j = 0; j < 2; ++j) {
            Buildings[i][j] = empty_building;
        }
    }
    return;
}

