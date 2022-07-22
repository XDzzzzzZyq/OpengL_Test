#include "Transform.h"

Transform::Transform()
{

}

Transform::~Transform()
{

}

void Transform::SetPos(const glm::vec3& pos)
{
	if (o_position != pos)
	{
		is_TransF_changed = true;
		o_Transform = glm::translate(o_Transform, -o_position);
		o_position = pos;
		/*ApplyTransform();*/
		o_Transform = glm::translate(o_Transform, o_position);
	}

}

void Transform::SetScale(const glm::vec3& scale)
{
	if (o_scale != scale)
	{
		is_TransF_changed = true;
		o_scale = scale;
		/*		ApplyTransform();*/
	}
}

void Transform::SetRot(const glm::vec3& rot)
{
	is_rot_changed = false;
	if (o_rot != rot)
	{
		is_TransF_changed = true;
		is_rot_changed = true;
		o_rot = rot;
		rotQua = glm::qua(glm::radians(o_rot));

		/*		ApplyTransform();*/
	}
}

void Transform::Move(const glm::vec3& d_pos)
{
	is_TransF_changed = true;
	o_Transform = glm::translate(o_Transform, -o_position);
	o_position += d_pos;
	/*ApplyTransform();*/
	o_Transform = glm::translate(o_Transform, o_position);
}

void Transform::Spin(const glm::vec3& anch, const glm::vec3& axis, const float& angle)
{
	is_invTransF_changed = true;
	rotQua = glm::qua<float>(glm::radians(o_rot));
	rotQua = glm::rotate(rotQua, angle, axis);
	rotMat = glm::mat4_cast(rotQua);
	o_Transform = glm::scale(glm::mat4(1.0f), o_scale);

	o_position -= anch;
	o_position = anch + rotMat * o_position;

	o_Transform = glm::translate(o_Transform, o_position);

	o_dir_up = rotMat * glm::vec3(0.0f, 1.0f, 0.0f);
	o_dir_right = rotMat * glm::vec3(1.0f, 0.0f, 0.0f);
}

void Transform::LookAt(const glm::vec3& tar)
{
	is_invTransF_changed = true;
	is_TransF_changed = false;
	
	//rotMat = glm::lookAt(o_position, tar, o_dir_up);
	rotQua = glm::quatLookAt(glm::normalize(tar - o_position), o_dir_up);
	rotMat = glm::mat4_cast(rotQua);
	
	o_dir_up = rotMat * glm::vec3(0.0f, 1.0f, 0.0f);
	o_dir_right = rotMat * glm::vec3(1.0f, 0.0f, 0.0f);

	o_Transform = glm::scale(glm::mat4(1.0f), o_scale);

	o_Transform = glm::translate(o_Transform, o_position);
}

void Transform::ApplyTransform()
{

	if (is_TransF_changed)
	{
		//DEBUG("apply");
		//rotMat = glm::mat4_cast(glm::qua<float>(glm::radians(o_rot)));
		rotMat = glm::mat4_cast(rotQua);
		o_Transform = glm::scale(glm::mat4(1.0f), o_scale);
		o_Transform = glm::translate(rotMat * o_Transform, o_position);

		if (is_rot_changed)
		{
			o_dir_up = rotMat * glm::vec3(0.0f, 1.0f, 0.0f);
			o_dir_right = rotMat * glm::vec3(1.0f, 0.0f, 0.0f);
			is_rot_changed = false;

		}
		is_invTransF_changed = true;
		is_TransF_changed = false;
	}

}

/*std::unordered_map<int, int, float> */

glm::mat4 Transform::GetInvTransform() const
{
	if (is_invTransF_changed)
	{
		glm::mat3 result = glm::mat3(o_Transform);
		//std::cout << result;
		o_InvTransform = glm::translate(glm::transpose(glm::mat4(result)), -1.0f * o_position);

		//o_InvTransform[3][3] = 1.0f;
		is_invTransF_changed = false;
		//std::cout << o_InvTransform;
		//std::cout << o_Transform;
		//DEBUG("+++++++++++++++++++++++++++++++")
		return o_InvTransform;
	}
	return o_InvTransform;
}