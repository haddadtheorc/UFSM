#ifndef __VETOR_H
#define __VETOR_H

#include <math.h>

//Uma nova classe, para armazenar e fazer as operações dos pontos em três dimensões - xyz

class vetor
{
public:
	float x, y, z;

	vetor( void )
	{
		x = y = z = 0.0;
	};

    vetor( const float tx, const float ty, const float tz )
	{
		x = tx;
		y = ty;
		z = tz;
	};

	vetor( const vetor& v )
	{
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;
	};

    void setValor( const float tx, const float ty, const float tz )
	{
		x = tx;
		y = ty;
		z = tz;
	};

	void setValor(const vetor v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
	};

	inline vetor operator + ( const vetor v )
	{
		vetor aux( x + v.x, y + v.y, z + v.z );
		return( aux );
	}

	inline vetor operator - ( const vetor v )
	{
		vetor aux( x - v.x, y - v.y, z - v.z );
		return( aux );
	}

	inline vetor operator * ( const float s )
	{
		vetor aux( x * s, y * s, z * s );
		return( aux );
	}

	inline vetor  operator / ( const float s )
	{
		vetor aux( x / s, y / s, z / s );
		return( aux );
	}

	inline float operator * ( const vetor v )
	{
		float aux = x * v.x + y * v.y + z * v.z;
		return( aux );
	}

	inline vetor operator ^ ( vetor v )
	{
		vetor aux( y * v.z - z * v.y,
			       z * v.x - x * v.z,
			       x * v.y - y * v.x );
		return( aux );
	}

	float norma( void )
	{
		return (float)( sqrt( x * x + y * y + z * z ) );
	}

	float distancia( vetor v )
	{
		return( (*this - v).norma() );
	}

	vetor normalize( void )
	{
		return( (*this) / (this->norma()) );
	}

	vetor extende(float val)
	{
		return ((*this) * (val) );
	}

};

#endif
