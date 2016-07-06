#pragma once

#include "Particle.h"

class Swarm{
	public:
		void setup();
		void update();
		void draw();
		void generateParticle(Particle temp);
		void eliminateParticle(int index);

		void overwriteAttributes(Particle temp);
		void overwriteParameters(Particle temp);

		int getNumParticles();

	private:
		vector <Particle> particles;
		Particle nextParticle;

};