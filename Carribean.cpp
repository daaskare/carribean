#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>   
#include <map> 
#include <set> 

using namespace std;

class Vector2d
{
    public:
    float _x;
    float _y;
	
	Vector2d()
	{
		_x = 0;
		_y = 0;
	}
	
	Vector2d(float x, float y)
	{
		_x = x;
		_y = y;
	}
	
	Vector2d(const Vector2d& v)
	{
		_x = v._x;
		_y = v._y;
	}
    
    inline float dist2(Vector2d& v)
    {
        return ((_x-v._x) * (_x-v._x)) + ((_y-v._y) * (_y-v._y));
    } 
	
    inline float dist(Vector2d& v)
    {
        return sqrt((_x-v._x) * (_x-v._x) + (_y-v._y) * (_y-v._y));
    } 
	
	inline bool operator==(const Vector2d &v)
	{
	    return ((_x == v._x) && (_y == v._y));
	}
	
	inline void operator+=(const Vector2d &v)
	{
		_x += v._x;
		_y += v._y;
	}
	
	inline void operator-=(const Vector2d &v)
	{
		_x -= v._x;
		_y -= v._y;
	}

	inline void operator*=(float c)
	{
		_x *= c;
		_y *= c;
	}

	inline void operator/=(float c)
	{
		// --- null division is not checked
		_x /= c;
		_y /= c;
	}

	inline Vector2d operator+(const Vector2d &v) const
	{
		return Vector2d(_x + v._x, _y + v._y);
	}

	inline Vector2d operator-(const Vector2d &v) const
	{
		return Vector2d(_x - v._x, _y - v._y);
	}

	inline Vector2d operator*(float k) const
	{
		return Vector2d(_x * k, _y * k);
	}

	inline Vector2d operator/(float k) const
	{
	// --- null division is not checked
		return Vector2d(_x / k, _y / k);
	}
	
	inline float norme() const
	{
	    return sqrt(_x*_x+_y*_y);
	}
	
	inline void normalize()
	{
        float norm = norme();
        if (norm > 0.001)
        {
 		    _x /= norm;
	    	_y /= norm;           
        }
        else
        {
            _x = 1.0f;
            _y = 0.0f;
        }
	}
	inline Vector2d rightVector()
	{
	    return Vector2d(-_y , _x);
	}
};

//Compute the dot product AB . AC
float DotProduct(Vector2d& pointA, Vector2d& pointB, Vector2d& pointC)
{
	Vector2d AB =  pointB - pointA;
	Vector2d AC =  pointC - pointA;
	
    float dot = AB._x * AC._x + AB._y * AC._y;

    return dot;
}

//Compute the cross product AB x AC
float CrossProduct(Vector2d& pointA, Vector2d& pointB, Vector2d& pointC)
{
	Vector2d AB =  pointB - pointA;
	Vector2d AC =  pointC - pointA;
	
    float cross = AB._x * AC._y - AB._y * AC._x;

    return cross;
}

//Compute the distance from AB to C
double LineToPointSignedDistance2D(Vector2d pointA, Vector2d pointB, Vector2d pointC)
{
	float normeAB = pointA.dist(pointB);
    float dist = CrossProduct(pointA, pointB, pointC) / normeAB;
    return dist;
} 



class Ship
{
    public:
    Ship()
    {
        _pos._x = 0.0f;
        _pos._y = 0.0f;
        _orient = 0;
        _speed = 0;
        _rhumLevel = 0;
        _previousGoal._x = 0.0f;
        _previousGoal._y = 0.0f;
        _previousFire = false;        
    }
    Ship(int x, int y, int o, int s, int r)
    {
        _pos._x = x;
        _pos._y = y;
        _orient = o;
        _speed = s;
        _rhumLevel = r;
        _previousGoal._x = 0.0f;
        _previousGoal._y = 0.0f;
        _previousFire = false;
    }
    void set(int x, int y, int o, int s, int r)
    {
        _pos._x = x;
        _pos._y = y;
        _orient = o;
        _speed = s;
        _rhumLevel = r;        
    }
    
    Vector2d _pos;
    int _orient;
    int _speed; 
    int _rhumLevel;
    Vector2d _previousGoal;
    bool _previousFire;
};

class Barrel
{
    public:
    Barrel(int x, int y, int r)
    {
        _pos._x = x;
        _pos._y = y;
        _rhumLevel = r;
    }
    
    Vector2d _pos;
    int _rhumLevel;    
};

class Mine
{
    public:
    Mine(int x, int y)
    {
        _pos._x = x;
        _pos._y = y;
    }
    
    Vector2d _pos;
};

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    std::map<int, Ship> myShips;
    std::set<int> myValidShipIds;
    std::vector<Ship> enemyShips;
    std::vector<Barrel> barrels;   
	std::vector<Mine> mines;   
    
    // game loop
    while (1) {
        int myShipCount; // the number of remaining ships
        cin >> myShipCount; cin.ignore();
        int entityCount; // the number of entities (e.g. ships, mines or cannonballs)
        cin >> entityCount; cin.ignore();
        
        myValidShipIds.clear();
        enemyShips.clear();
        barrels.clear();
        barrels.reserve(entityCount);
		mines.clear();
        
        for (int i = 0; i < entityCount; i++) {
            int entityId;
            string entityType;
            int x;
            int y;
            int arg1;
            int arg2;
            int arg3;
            int arg4;
            cin >> entityId >> entityType >> x >> y >> arg1 >> arg2 >> arg3 >> arg4; cin.ignore();
            
            if (entityType=="SHIP")
            {
                if (arg4 == 1)
                {
                    if (myShips.find(entityId)!=myShips.end())
                    {
                        myShips[entityId].set(x, y, arg1, arg2, arg3);
                    }
                    else
                    {
                        myShips[entityId]=Ship(x, y, arg1, arg2, arg3);
                    }
                    myValidShipIds.insert(entityId);
                }
                else
                {
                    enemyShips.push_back(Ship(x, y, arg1, arg2, arg3));
                    //cerr << "Debug messages... enemyShips x " << x << " y " << y << " o " << arg1 << " s " << arg2 << endl; 
                }
            }
            else if (entityType=="BARREL")
            {
                barrels.push_back(Barrel(x, y, arg1));
            }
            else if (entityType=="MINE")
            {
                mines.push_back(Mine(x, y));
            }           
            
        }
        
        for (std::set<int>::iterator it = myValidShipIds.begin(); it != myValidShipIds.end(); it++) {
            Ship& myShip = myShips[*it];

			Vector2d goal = myShip._pos;
			
            // Write an action using cout. DON'T FORGET THE "<< endl"
            // To debug: cerr << "Debug messages..." << endl;
            int nearest_dist2 = 10000000;
            int nearestBarrelId = -1;
            for (int b = 0; b < barrels.size(); b++) {
                 int dist2=barrels[b]._pos.dist2(myShip._pos);
                 //cerr << "Debug messages... dist2 " << dist2 << " b " << b << endl; 
                 if (dist2 < nearest_dist2)
                 {
                     bool mineNearBarrel = false;
                     for (int m = 0; m < mines.size(); m++) {
                         int distMin2=barrels[b]._pos.dist2(mines[m]._pos);
                         if (distMin2 <= 1.01f)
                         {
                             mineNearBarrel = true;
                             break;
                         }   
                     }
     
                     if (!mineNearBarrel)
                     {
                         nearestBarrelId = b;
                         nearest_dist2 = dist2;
                     }
                 }
            }
            
            
			int nearest_enemy_dist2 = 10000000;
			int nearestEnemyId = -1;
			for (int e = 0; e < enemyShips.size(); e++) {
				 int dist2=enemyShips[e]._pos.dist2(myShip._pos);
				 //cerr << "Debug messages... dist2 " << dist2 << " b " << b << endl; 
				 if (dist2 < nearest_enemy_dist2)
				 {
					 nearestEnemyId = e;
					 nearest_enemy_dist2 = dist2;
				 }
			}
			
			if (nearestBarrelId >= 0)
			{
				goal = barrels[nearestBarrelId]._pos;
				//cerr << "Debug messages... goal " << goal._x << "  " <<  goal._y << endl; 
			}
			else
			{	
				if (nearestEnemyId >= 0)
				{
					// charge
					goal = enemyShips[nearestEnemyId]._pos;		
				}
			 
			}
			
			for (int m = 0; m < mines.size(); m++) {
				float dist_mine = LineToPointSignedDistance2D(myShip._pos, goal, mines[m]._pos);
				
				if (fabs(dist_mine) < 1.5f)
				{
					float normeAB = myShip._pos.dist(goal);
					float distSurAxe = DotProduct(myShip._pos, goal, mines[m]._pos)/normeAB;
					
					if ((distSurAxe > 0) && (distSurAxe < normeAB))
					{
						// danger : mine dans la direction à atteindre
					    //cerr << "Debug messages... distSurAxe " << distSurAxe << " normeAB " << normeAB << endl;
					    Vector2d dirMine = mines[m]._pos - myShip._pos;
					    dirMine.normalize();
					    int sens = (dist_mine > 0)?-1:1;
					    goal = mines[m]._pos + dirMine.rightVector()*(2.0*sens);		    
					}
				}

            }
        
            if ((goal == myShip._previousGoal) && (myShip._previousFire == false))
            {
                if ((nearestEnemyId != -1) && (nearest_enemy_dist2 < 100))
                {
                    float anticipation = 1.0f + sqrt(nearest_enemy_dist2)*.33;
                    float dx = anticipation*enemyShips[nearestEnemyId]._speed * cosf(enemyShips[nearestEnemyId]._orient * M_PI/3);
                    float dy = -anticipation*enemyShips[nearestEnemyId]._speed * sinf(enemyShips[nearestEnemyId]._orient * M_PI/3);
                    cout << "FIRE " << (int)(enemyShips[nearestEnemyId]._pos._x + dx) << " " << (int)(enemyShips[nearestEnemyId]._pos._y + dy) << endl;
                    myShip._previousFire = true;
                    continue;
                }      
            }
                 
            //cerr << "Debug messages... nearest_dist2 " << nearest_dist2 << " nearestBarrelId " << nearestBarrelId << endl;
            myShip._previousFire = false;
            myShip._previousGoal = goal;
            cout << "MOVE " << (int)goal._x << " " << (int)goal._y << endl; // Any valid action, such as "WAIT" or "MOVE x y"
        }
    }
}