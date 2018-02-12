//headers

Missile missile;
Plane plane;
FuzzyLogic_Missile * flm = new FuzzyLogic_Missile(100.0f);

#define CITYNUMBER	5

//Cities
struct City
{
	City() {radius = 1.0f; position = Point2D(); damage = 50.0f;};
	float radius;
	Point2D position;
	float damage;
	int red;
	int green;
	int blue;
};

City cities[CITYNUMBER];

/* Client Code ... */
void ReadDamageValue()
{
	float dm = 10.0f;//outside any city
	//calculate dm using the position of the plane in an area
	float dist = 0.0f;
	for(int i = 0; i < CITYNUMBER; i++)
	{
		float dx = cities[i].position.x - plane.m_position.x;
		float dy = cities[i].position.y - plane.m_position.y;
        dist = sqrtf(dx*dx + dy*dy);

		if(dist < (cities[i].radius + plane.m_radius))
		{
			dm = cities[i].damage;
			break;
		}
	}

	flm->SetCorrectedDamageValue(dm);
}

void ReadFuelValue()
{
	flm->SetFuelValue(flm->GetFuelValue() - 0.01f);	
}

void ResetGame()
{
	missile = Missile();
	plane = Plane();

	missile.m_position.x = 70;
	missile.m_position.y = 70;
	missile.m_speed = 1.9f;
	missile.m_direction.x = 1.0f;
	missile.m_direction.y = 0.0f;
	missile.m_direction.Normalize();


	plane.m_position.x = 170;
	plane.m_position.y = 400;
	plane.m_speed = 1.8f;
	plane.m_direction.x = 1.5f;
	plane.m_direction.y = -1.0f;
	plane.m_direction.Normalize();
	
	
    //cities
	cities[0].radius = 60.0f;
	cities[0].damage = 50.0f;
	cities[0].position.x = 110;
	cities[0].position.y = 110;
	cities[0].red = 255;
	cities[0].green = 128;
	cities[0].blue = 128;

	cities[1].radius = 100.0f;
	cities[1].damage = 90.0f;
	cities[1].position.x = 300;
	cities[1].position.y = 200;
	cities[1].red = 255;
	cities[1].green = 8;
	cities[1].blue = 8;

	cities[2].radius = 60.0f;
	cities[2].damage = 45.0f;
	cities[2].position.x = 500;
	cities[2].position.y = 90;
	cities[2].red = 255;
	cities[2].green = 160;
	cities[2].blue = 160;

	cities[3].radius = 90.0f;
	cities[3].damage = 75.0f;
	cities[3].position.x = 495;
	cities[3].position.y = 350;
	cities[3].red = 255;
	cities[3].green = 55;
	cities[3].blue = 55;

	cities[4].radius = 44.0f;
	cities[4].damage = 83.0f;
	cities[4].position.x = 99;
	cities[4].position.y = 300;
	cities[4].red = 255;
	cities[4].green = 25;
	cities[4].blue = 25;
}

void Client_Initialize()
{
	ResetGame();
}

void Client_ShutDown()
{
}

void Client_Handle()//loop
{
	if(initializeMissilePosition && initializeMissileDirection)
	{
		//Fuzzy Logic Updates
		ReadDamageValue();
		ReadFuelValue();
		flm->CalculateAttackRate();
        flm->UpdateCorrection(&missile,&plane);
	
	
		//update missile's position
		missile.m_position.x += missile.m_direction.x * missile.m_speed;
		missile.m_position.y += missile.m_direction.y * missile.m_speed;

		//Control Plane Movement
		if(Keyboard_IsPressed(VK_LEFT))
		{
			plane.m_direction.x = -1;
			plane.m_direction.y = 0;
		}
		if(Keyboard_IsPressed(VK_RIGHT))
		{
			plane.m_direction.x = 1;
			plane.m_direction.y = 0;
		}
		if(Keyboard_IsPressed(VK_UP))
		{
			plane.m_direction.x = 0;
			plane.m_direction.y = -1;
		}
		if(Keyboard_IsPressed(VK_DOWN))
		{
			plane.m_direction.x = 0;
			plane.m_direction.y = 1;
		}
	}
	//update plane's position
	plane.m_position.x += plane.m_direction.x * plane.m_speed;
	plane.m_position.y += plane.m_direction.y * plane.m_speed;

	
	//do not let the plane go outside the area
	
	
	//hit target test
	float px = plane.m_position.x-missile.m_position.x;
	float py = plane.m_position.y-missile.m_position.y;
	float dist = sqrtf(px*px + py*py);
	if(dist < 8)
	{
		MessageBox(hWnd,"Plane Hit.","Radar Info.",MB_OK);
		ResetGame();
	}
	if(flm->GetFuelValue() <= 0.0f)
	{
		MessageBox(hWnd,"Pilot Win.","Base Report.",MB_OK);
		ResetGame();
	}
}