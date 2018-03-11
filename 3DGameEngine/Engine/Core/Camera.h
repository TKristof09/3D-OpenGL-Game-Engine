#ifndef CAMERA_H
#define CAMERA_H

#include <glm\ext.hpp> // used to make vectors to string

#define GLM_ENABLE_EXPERIMENTAL
#include <glm\glm.hpp>
#include <glm\gtx\rotate_vector.hpp>


enum Camera_Movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};
// TODO maybe implement in a .cpp
class Camera
{
public:
	Camera(float fov, float aspect, float zNear, float zFar):
		m_fov(fov),
		m_aspect(aspect),
		m_zNear(zNear),
		m_zFar(zFar),
		m_position(glm::vec3(0, 0, 0)),
		m_forward(glm::vec3(0, 0, -1)),
		m_up(glm::vec3(0, 1, 0))
	{}

	Camera(const glm::vec3& pos, glm::vec3& forward, glm::vec3& up, float fov, float aspect, float zNear, float zFar):
		m_fov(fov),
		m_aspect(aspect),
		m_zNear(zNear),
		m_zFar(zFar),

		m_position(pos),
		m_forward(normalize(forward)),
		m_up(normalize(up))
		{}
			

	inline glm::mat4 GetViewProjection() const
	{
		return glm::perspective(glm::radians(m_fov), m_aspect, m_zNear, m_zFar) * lookAt(m_position, m_position + m_forward, m_up);
	}


	inline const glm::vec3* GetPos() const { return &m_position; };
	inline void SetPos(glm::vec3 pos) { m_position = pos; };

	inline const glm::vec3* GetForward() const { return &m_forward; };
	inline const glm::vec3* GetUp() const { return &m_up; };
	inline glm::vec3 GetLeft() const { return cross(m_up, m_forward); };
	inline glm::vec3 GetRight() const { return cross(m_forward, m_up); };
    
	
	

	/*void Translate(vec3 direction, float amount)
	{		
		vec3 translationVector = -direction * amount;
		
		camera = translate(camera, translationVector);
	}*/

	// TODO make global ones too and maybe place the rotations in a separate header
	// Local rotations
	void RotateX(float angle)
	{
		m_forward = glm::rotate(m_forward, -angle, GetRight());
		glm::vec3 right = glm::cross(m_forward, *GetUp());
		m_up = glm::cross(right, m_forward);
	}

	void RotateY(float angle)
	{
		m_forward = glm::rotate(m_forward, angle, m_up);
	}

	void RotateZ(float angle)
	{
		m_up = glm::rotate(m_up, angle, *GetForward());
	}

	
	//TODO translation by vector
	//maybe m_position += translationVector;

	void Translate(Camera_Movement direction, float amount)
	{
		switch (direction)
		{
			case FORWARD:
				{
				m_position += m_forward * amount;
				break;
				}
			case BACKWARD:
				{
					m_position -= m_forward * amount;
					break;
				}
			case LEFT:
				{
					m_position -= GetRight() * amount;
					break;
				}
			case RIGHT:
				{
					m_position += GetRight() * amount;
					break;
				}
			case UP:
				{
					m_position += m_up * amount;
					break;
				}
			case DOWN:
				{
					m_position -= m_up * amount;
					break;
				}
			default:
				{
					break;
				}
		}
	}


private:	

	float m_fov;
	float m_aspect;
	float m_zNear;
	float m_zFar;
	
	glm::vec3 m_position;
	glm::vec3 m_forward;
	glm::vec3 m_up;
};
#endif