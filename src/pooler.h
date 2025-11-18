//Copyright 2K Games, Engineering Graduate Program. All rights reserved. DO NOT redistribute.

#ifndef POOLER_H
#define POOLER_H

#include <memory>
#include <list>
#include <vector>

#include "enemy.h"
#include "vector2d.h"



class Pooler {
   public:
    explicit Pooler(size_t minimumPoolSize);


    size_t PoolSize();

    void Clear();

    
    Enemy* SpawnEnemy(const Vector2D& position);

    
    void DespawnEnemy(Enemy* enemy);

    
    std::vector<Enemy*> GetActiveEnemies() const;

    ~Pooler();

   private:
    
    std::list<Enemy*> activeEnemies;

    
    std::list<Enemy*> inactiveEnemies;

    size_t minimumPoolSize;

    Enemy* CreateEnemy();
    void Prewarm();
    void ResetEnemyState(Enemy& enemy);
};

#endif  
