#pragma once

int getLevel(int diem)
{
	return (diem / 5);
}

int getSleepTime(int level)
{
	return (level < 10) ? 100 - level * 10 : 10;
}

int getMaxObstacle(int level)
{
	if (level > 30)
		return 8;

	if (level > 10)
	{
		return 5 + (level - 10) / 5;
	}
	return (13 + level) / 4;
}

int getRateGenerateObstacle(int level)
{
	if (level > 30)
		return 25;

	if (level > 10)
	{
		return 5 * (1 + level % 5);
	}
	return 5 * (1 + (level + 1) % 4);
}

int getMaxAmplitude(int level)
{
	if (level > 30)
		return 4;
	return (level > 10) ? level / 5 - 1 : 0;
	//return 4;
}

int getRateFluctuation(int level)
{
	if (level > 30)
		return 5;
	return (level > 10) ? 1 * (1 + level % 5) : 0;
}

void updateLevelStats(Level &stats)
{
	stats.level = getLevel(stats.diem);	//update level

	//update stat
	stats.sleep_time = getSleepTime(stats.level);
	stats.max_obstacle = getMaxObstacle(stats.level);
	stats.rate_generate_obstacle = getRateGenerateObstacle(stats.level);
	stats.max_amplitude = getMaxAmplitude(stats.level);
	stats.rate_fluctuation = getRateFluctuation(stats.level);
}