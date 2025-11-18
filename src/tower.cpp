//Copyright 2K Games, Engineering Graduate Program. All rights reserved. DO NOT redistribute.

#include "tower.h"
#include "logger.h"
#include "constants.h"  

#include <limits>
#include <cstdlib>  

Tower::Tower(int x, int y, int rateOfFire)
    : position({x, y}),
      rateOfFire(rateOfFire),
      lastFireTime(std::chrono::steady_clock::now()),
      bAutoFire(true)
    {}

void Tower::Update(std::vector<Enemy*> enemies,
                   std::vector<Bullet>& bullets) {
    if (bAutoFire) {
        FireAtEnemy(enemies, bullets);
    }
}

void Tower::FireAtEnemy(const std::vector<Enemy*>& enemies,
                        std::vector<Bullet>& bullets) {
    const auto currentTime = std::chrono::steady_clock::now();
    const auto timeElapsed =
        std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastFireTime);

    if (timeElapsed < std::chrono::milliseconds(rateOfFire)) {
        return;
    }

    Enemy* closestEnemy = FindClosestEnemy(enemies);
    if (!closestEnemy) {
        return;
    }

    const int distance = CalculateDistance(closestEnemy->GetPosition(), position);
    if (distance > ENEMYRANGE) {
        return;
    }

    FireBulletAtEnemy(*closestEnemy, bullets);
    lastFireTime = currentTime;

    Logger::GetInstance().Log(bAutoFire ? "Auto fired at enemy"
                                        : "Manual fired at enemy");
}

bool Tower::GetAutoFire() const { return bAutoFire; }

void Tower::SetAutoFire(bool autoFire) { bAutoFire = autoFire; }

void Tower::ManualFire(std::vector<Enemy*> enemies,
                       std::vector<Bullet>& bullets) {
    FireAtEnemy(enemies, bullets);
}

int Tower::CalculateDistance(const Vector2D& a, const Vector2D& b) const {
    
    return static_cast<int>(std::abs(static_cast<long>(a.x - b.x)) + 
                           std::abs(static_cast<long>(a.y - b.y)));
}

Enemy* Tower::FindClosestEnemy(const std::vector<Enemy*>& enemies) const {
    Enemy* bestEnemy = nullptr;
    int bestDistance = std::numeric_limits<int>::max();

    for (Enemy* enemy : enemies) {
        if (!enemy) continue;

        const Vector2D enemyPos = enemy->GetPosition();
        int d = CalculateDistance(enemyPos, position);
        if (d < bestDistance) {
            bestDistance = d;
            bestEnemy = enemy;
        }
    }

    return bestEnemy;
}

void Tower::FireBulletAtEnemy(Enemy& enemy, std::vector<Bullet>& bullets) {
    Vector2D direction = {0, 0};
    const Vector2D& enemyPos = enemy.GetPosition();
    
    if (enemyPos.x > position.x) direction.x = 1;
    if (enemyPos.x < position.x) direction.x = -1;
    if (enemyPos.y > position.y) direction.y = 1;
    if (enemyPos.y < position.y) direction.y = -1;

    
    bullets.emplace_back(position, direction);
}
