#include "Swarm.h"

void Swarm::setup()
{
	particles.reserve(MAX_PARTICLES);
}

void Swarm::update()
{
	for (unsigned int i=0; i<particles.size(); ++i){
		particles[i].update();
		if (particles[i].isDead)
			particles.erase(particles.begin() + i);
	}
}

void Swarm::draw()
{
	for (unsigned int i=0 ; i<particles.size(); ++i){
		//particles[i].draw(camera.getPosition());
		particles[i].draw();
	}
}

void Swarm::overwriteAttributes(Particle temp)
{
	for (unsigned int i=0; i<particles.size(); ++i){
		particles[i].resetLinks();	//TODO: make this line not necessary
		particles[i].setAttributes(&(temp.attributes));
	}
}

void Swarm::overwriteParameters(Particle temp)
{
	for (unsigned int i=0; i<particles.size(); ++i){
		particles[i].setParameters(&(temp.parameters));
	}
}

void Swarm::generateParticle(Particle temp)
{	
	if (particles.size() < MAX_PARTICLES) {
		particles.push_back(Particle(temp.getPosition(), temp.velocity, &(temp.parameters), &(temp.attributes), &particles));
	}
}

void Swarm::eliminateParticle(int index){
	particles[index].resetLinks();
	particles[index].isDead = true;
}

int Swarm::getNumParticles()
{
	return particles.size();
}