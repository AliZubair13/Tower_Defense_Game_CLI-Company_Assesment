#ifdef RUNNING_TESTS

#include <cassert>
#include <sstream>
#include <iostream>
#include "pooler.h"
#include "enemy.h"
#include "tower.h"
#include "logger.h"
#include "vector2d.h"

#include <cstdlib>

// Disable screen manipulation during tests
#define DISABLE_SCREEN_MANIPULATION() do { \
    _putenv("TERM=dumb"); \
} while(0)

// Restore screen manipulation after tests
#define RESTORE_SCREEN_MANIPULATION() do { \
    _putenv("TERM="); \
} while(0)

void test_memory_pool() {
    DISABLE_SCREEN_MANIPULATION();
    Pooler pool(10); // Create pool with minimum size 10
    
    // Test pool allocation
    Vector2D pos1{5, 5};
    Enemy* enemy1 = pool.SpawnEnemy(pos1);
    assert(enemy1 != nullptr);
    assert(enemy1->IsActive());
    assert(pool.GetActiveEnemies().size() == 1);
    
    Vector2D pos2{10, 10};
    Enemy* enemy2 = pool.SpawnEnemy(pos2);
    assert(enemy2 != nullptr);
    assert(enemy2->IsActive());
    assert(pool.GetActiveEnemies().size() == 2);
    assert(enemy1 != enemy2);
    
    // Test pool deallocation
    pool.DespawnEnemy(enemy1);
    assert(!enemy1->IsActive());
    assert(pool.GetActiveEnemies().size() == 1);
    
    Enemy* enemy3 = pool.SpawnEnemy(pos1);
    assert(enemy3->IsActive());
    assert(pool.GetActiveEnemies().size() == 2);
    
    std::cout << "Memory pool tests passed!" << std::endl;
}

void test_tower_targeting() {
    Tower tower(10, 10, 1); // x, y, rate of fire
    
    Enemy enemy1;
    enemy1.Activate(Vector2D{5, 5});
    
    Enemy enemy2;
    enemy2.Activate(Vector2D{15, 15});
    
    std::vector<Enemy*> enemies = {&enemy1, &enemy2};
    
    // Test closest enemy calculation
    Enemy* closest = tower.FindClosestEnemy(enemies);
    assert(closest == &enemy1); // enemy1 should be closer
    
    int dist1 = tower.CalculateDistance(tower.position, enemy1.GetPosition());
    int dist2 = tower.CalculateDistance(tower.position, enemy2.GetPosition());
    assert(dist1 < dist2);
    
    std::cout << "Tower targeting tests passed!" << std::endl;
}

void test_logger() {
    Logger& logger = Logger::GetInstance();
    
    // Test log writing
    std::string testMessage = "Test log message";
    logger.Log(testMessage);
    logger.Flush();
    
    std::cout << "Logger tests passed!" << std::endl;
}

int run_tests() {
    std::cout << "Running tests..." << std::endl;
    
    test_memory_pool();
    test_tower_targeting();
    test_logger();
    
    std::cout << "All tests passed!" << std::endl;
    RESTORE_SCREEN_MANIPULATION();
    return 0;
}

#endif // RUNNING_TESTS