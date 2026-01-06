package components

import (
	"math"

	. "froglib/math"
)

type Rigidbody struct {
	velocity     Vec2
	acceleration Vec2
	mass         float64
	drag         float64
	isStatic     bool
	inverseMass  float64
}

func NewRigidbody(mass float64, drag float64, isStatic bool) *Rigidbody {
	var inverseMass float64
	if isStatic || mass == 0.0 {
		inverseMass = 0.0
	} else {
		inverseMass = 1.0 / mass
	}

	rigidbody := Rigidbody{
		velocity:     NewVec2(0.0, 0.0),
		acceleration: NewVec2(0.0, 0.0),
		mass:         mass,
		drag:         drag,
		isStatic:     isStatic,
		inverseMass:  inverseMass,
	}

	return &rigidbody
}

func (r *Rigidbody) ApplyForce(force Vec2) {
	if r.isStatic {
		return
	}
	r.acceleration = r.acceleration.Add(force.Scale(r.inverseMass))
}

func (r *Rigidbody) ApplyImpulse(impulse Vec2) {
	if r.isStatic {
		return
	}
	r.velocity = r.velocity.Add(impulse.Scale(r.inverseMass))
}

func (r *Rigidbody) Integrate(position *Vec2) {
	if r.isStatic {
		return
	}

	// update velocity with acceleration
	r.velocity = r.velocity.Add(r.acceleration)

	// apply drag
	r.velocity = r.velocity.Scale(math.Exp(-r.drag))

	// update position with velocity
	*position = position.Add(r.velocity)

	// reset acceleration for next frame
	r.acceleration = NewVec2(0.0, 0.0)
}
