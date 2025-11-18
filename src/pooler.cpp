//Copyright 2K Games, Engineering Graduate Program. All rights reserved. DO NOT redistribute.

#include "pooler.h"

#include <algorithm>

Pooler::Pooler(size_t minimumPoolSize)
    : minimumPoolSize(minimumPoolSize) {
    Prewarm();
}

Pooler::~Pooler() {
    
    for (auto* e : activeEnemies) {
        delete e;
    }
    for (auto* e : inactiveEnemies) {
        delete e;
    }
}

void Pooler::Prewarm() {
    
    for (size_t i = 0; i < minimumPoolSize; ++i) {
        inactiveEnemies.push_back(CreateEnemy());
    }
}

size_t Pooler::PoolSize() {
    return activeEnemies.size() + inactiveEnemies.size();
}

Enemy* Pooler::CreateEnemy() {
    return new Enemy();
}

void Pooler::ResetEnemyState(Enemy& enemy) {
    enemy.Deactivate();
    enemy.SetVelocity(0.0);
    enemy.SetTarget(enemy.GetPosition());
}

void Pooler::Clear() {
    
    for (auto* e : activeEnemies) {
        ResetEnemyState(*e);
        inactiveEnemies.push_back(e);
    }
    activeEnemies.clear();
}

Enemy* Pooler::SpawnEnemy(const Vector2D& position) {
    Enemy* enemy = nullptr;

    if (!inactiveEnemies.empty()) {
        
        enemy = inactiveEnemies.front();
        inactiveEnemies.pop_front();
    } else {
        
        enemy = CreateEnemy();
    }

    
    enemy->Activate(position);
    enemy->SetVelocity(0.0);
    enemy->SetTarget(position);

    
    activeEnemies.push_back(enemy);

    return enemy;
}

void Pooler::DespawnEnemy(Enemy* enemy) {
    if (!enemy) return;

    
    auto it = std::find(activeEnemies.begin(), activeEnemies.end(), enemy);
    if (it != activeEnemies.end()) {
        
        Enemy* e = *it;
        ResetEnemyState(*e);
        inactiveEnemies.push_back(e);
        activeEnemies.erase(it);
    }
}

std::vector<Enemy*> Pooler::GetActiveEnemies() const {
    std::vector<Enemy*> out;
    out.reserve(activeEnemies.size());
    for (auto* e : activeEnemies) {
        out.push_back(e);
    }
    return out;
}
