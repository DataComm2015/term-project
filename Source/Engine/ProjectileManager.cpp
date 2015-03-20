#include "ProjectileManager.h"

std::set<Marx::Projectile*> Manager::ProjectileManager::projectile_pool;

using namespace Manager;

Marx::Projectile* ProjectileManager::
getProjectile(float x, float y, Marx::Controller * ctrl = nullptr, float h = 1.0, float w = 1.0)
{
	Marx::Projectile *temp;
	if (projectile_pool.size() <= 0)
	{
		return new Marx::Projectile(x, y, ctrl, h, w);
	} else
	{
		temp = *projectile_pool.begin();
		projectile_pool.erase(*projectile_pool.begin());
		return temp;
	}
}

void ProjectileManager::
enqueue(Marx::Projectile* projectile)
{
	projectile_pool.insert(projectile);
}

void ProjectileManager::
dequeue(Marx::Projectile* projectile)
{
	projectile_pool.erase(projectile);
}
