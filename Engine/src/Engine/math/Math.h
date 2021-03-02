#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>

namespace Engine
{
	

	// TODO: refactor
	namespace glm_helper {

		template<typename T>
		struct glm_mat;

		template<glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
		struct glm_mat<glm::mat<C, R, T, Q>> {

			GLM_FUNC_QUALIFIER static glm::mat<C, R, T, Q> all(T val) {
				glm::mat<C, R, T, Q> mat{};
				for (glm::length_t i = 0; i < mat.length(); ++i) {
					mat[i] = glm::vec<C, T, Q>(val);
				}
				return mat;
			}
		
		};



	}


	glm::vec3 ScreenToWorld(const glm::mat4& viewProjectionMatrix, const glm::vec2& mousePosition, const glm::vec2& screenDimensions);
	//glm::vec3 ScreenToWorld(const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const glm::vec2& mousePosition, const glm::vec4& viewPort);





	/* GLM TYPE CHECKING */

	// vectors
	template<typename T>
	struct is_glm_vector { static const bool value = false; };

	template<typename T, glm::length_t L, glm::qualifier Q>
	struct is_glm_vector<glm::vec<L, T, Q>> { static const bool value = true; };

	// matrices
	template<typename T>
	struct is_glm_matrix { static const bool value = false; };

	template<typename T, glm::length_t C, glm::length_t R, glm::qualifier Q>
	struct is_glm_matrix <glm::mat<C, R, T, Q>> { static const bool value = true; };


	/* GENERIC FUNCTIONS FOR GLM+ */
	template<typename genType>
	GLM_FUNC_QUALIFIER genType Map(const genType value, const genType minIn, const genType maxIn, const genType minOut, const genType maxOut)
	{
		return minOut + (maxOut - minOut) * ((value - minIn) / (maxIn - minIn));
	}

	template<glm::length_t L, typename T, glm::qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR glm::vec<L, T, Q> Map(glm::vec<L, T, Q> const& value, glm::vec<L, T, Q> const& minIn, glm::vec<L, T, Q> const& maxIn, glm::vec<L, T, Q> const& minOut, glm::vec<L, T, Q> const& maxOut)
	{
		return compute_map_vector<L, T, Q, glm::detail::is_aligned<Q>::value>::call(value, minIn, maxIn, minOut, maxOut);
	}

	template<glm::length_t L, typename T, glm::qualifier Q, bool Aligned>
	struct compute_map_vector
	{
		GLM_FUNC_QUALIFIER static glm::vec<L, T, Q> call(glm::vec<L, T, Q> const& value, glm::vec<L, T, Q> const& minIn, glm::vec<L, T, Q> const& maxIn, glm::vec<L, T, Q> const& minOut, glm::vec<L, T, Q> const& maxOut)
		{
			return functor5<glm::vec, L, T, T, Q>::call(Map, value, minIn, maxIn, minOut, maxOut);
		}
	};

	// TODO: compute_map_matrix


	/* ADDITIONAL GLM FUNCTORS */

	/* FUNCTOR 0 */
	template<template<glm::length_t L, typename T, glm::qualifier Q> class vec, glm::length_t L, typename R, typename T, glm::qualifier Q>
	struct functor0 {};

	template<template<glm::length_t L, typename T, glm::qualifier Q> class vec, typename R, typename T, glm::qualifier Q>
	struct functor0<vec, 1, R, T, Q>
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static vec<1, R, Q> call(R(*Func) ())
		{
			return vec<1, R, Q>(Func());
		}
	};

	template<template<glm::length_t L, typename T, glm::qualifier Q> class vec, typename R, typename T, glm::qualifier Q>
	struct functor0<vec, 2, R, T, Q>
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static vec<2, R, Q> call(R(*Func) ())
		{
			return vec<2, R, Q>(Func(), Func());
		}
	};

	template<template<glm::length_t L, typename T, glm::qualifier Q> class vec, typename R, typename T, glm::qualifier Q>
	struct functor0<vec, 3, R, T, Q>
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static vec<3, R, Q> call(R(*Func) ())
		{
			return vec<3, R, Q>(Func(), Func(), Func());
		}
	};

	template<template<glm::length_t L, typename T, glm::qualifier Q> class vec, typename R, typename T, glm::qualifier Q>
	struct functor0<vec, 4, R, T, Q>
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static vec<4, R, Q> call(R(*Func) ())
		{
			return vec<4, R, Q>(Func(), Func(), Func(), Func());
		}
	};


	/* FUNCTOR 5 */
	template<template<glm::length_t L, typename T, glm::qualifier Q> class vec, glm::length_t L, typename R, typename T, glm::qualifier Q>
	struct functor5 {};

	template<template<glm::length_t L, typename T, glm::qualifier Q> class vec, typename R, typename T, glm::qualifier Q>
	struct functor5<vec, 1, R, T, Q>
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static vec<1, R, Q> call(R(*Func) (T x, T y, T z, T aa, T ab), vec<1, T, Q> const& v1, vec<1, T, Q> const& v2, vec<1, T, Q> const& v3, vec<1, T, Q> const& v4, vec<1, T, Q> const& v5)
		{
			return vec<1, R, Q>(Func(v1.x, v2.x, v3.x, v4.x, v5.x));
		}
	};

	template<template<glm::length_t L, typename T, glm::qualifier Q> class vec, typename R, typename T, glm::qualifier Q>
	struct functor5<vec, 2, R, T, Q>
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static vec<2, R, Q> call(R(*Func) (T x, T y, T z, T aa, T ab), vec<2, T, Q> const& v1, vec<2, T, Q> const& v2, vec<2, T, Q> const& v3, vec<2, T, Q> const& v4, vec<2, T, Q> const& v5)
		{
			return vec<2, R, Q>(Func(v1.x, v2.x, v3.x, v4.x, v5.x), Func(v1.y, v2.y, v3.y, v4.y, v5.x));
		}
	};

	template<template<glm::length_t L, typename T, glm::qualifier Q> class vec, typename R, typename T, glm::qualifier Q>
	struct functor5<vec, 3, R, T, Q>
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static vec<3, R, Q> call(R(*Func) (T x, T y, T z, T aa, T ab), vec<3, T, Q> const& v1, vec<3, T, Q> const& v2, vec<3, T, Q> const& v3, vec<3, T, Q> const& v4, vec<3, T, Q> const& v5)
		{
			return vec<3, R, Q>(Func(v1.x, v2.x, v3.x, v4.x, v5.x), Func(v1.y, v2.y, v3.y, v4.y, v5.x), Func(v1.z, v2.z, v3.z, v4.z, v5.z));
		}
	};

	template<template<glm::length_t L, typename T, glm::qualifier Q> class vec, typename R, typename T, glm::qualifier Q>
	struct functor5<vec, 4, R, T, Q>
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static vec<4, R, Q> call(R(*Func) (T x, T y, T z, T aa, T ab), vec<4, T, Q> const& v1, vec<4, T, Q> const& v2, vec<4, T, Q> const& v3, vec<4, T, Q> const& v4, vec<4, T, Q> const& v5)
		{
			return vec<4, R, Q>(Func(v1.x, v2.x, v3.x, v4.x, v5.x), Func(v1.y, v2.y, v3.y, v4.y, v5.x), Func(v1.z, v2.z, v3.z, v4.z, v5.z), Func(v1.w, v2.w, v3.w, v4.w, v5.w));
		}
	};

	/* FUNCTOR 6 */
	template<template<glm::length_t L, typename T, glm::qualifier Q> class vec, glm::length_t L, typename R, typename T, glm::qualifier Q>
	struct functor6 {};

	template<template<glm::length_t L, typename T, glm::qualifier Q> class vec, typename R, typename T, glm::qualifier Q>
	struct functor6<vec, 1, R, T, Q>
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static vec<1, R, Q> call(R(*Func) (T x, T y, T z, T aa, T ab, T ac), vec<1, T, Q> const& v1, vec<1, T, Q> const& v2, vec<1, T, Q> const& v3, vec<1, T, Q> const& v4, vec<1, T, Q> const& v5, vec<1, T, Q> const& v6)
		{
			return vec<1, R, Q>(Func(v1.x, v2.x, v3.x, v4.x, v5.x, v6.x));
		}
	};

	template<template<glm::length_t L, typename T, glm::qualifier Q> class vec, typename R, typename T, glm::qualifier Q>
	struct functor6<vec, 2, R, T, Q>
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static vec<2, R, Q> call(R(*Func) (T x, T y, T z, T aa, T ab, T ac), vec<2, T, Q> const& v1, vec<2, T, Q> const& v2, vec<2, T, Q> const& v3, vec<2, T, Q> const& v4, vec<2, T, Q> const& v5, vec<2, T, Q> const& v6)
		{
			return vec<2, R, Q>(Func(v1.x, v2.x, v3.x, v4.x, v5.x, v6.x), Func(v1.y, v2.y, v3.y, v4.y, v5.x, v6.y));
		}
	};

	template<template<glm::length_t L, typename T, glm::qualifier Q> class vec, typename R, typename T, glm::qualifier Q>
	struct functor6<vec, 3, R, T, Q>
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static vec<3, R, Q> call(R(*Func) (T x, T y, T z, T aa, T ab, T ac), vec<3, T, Q> const& v1, vec<3, T, Q> const& v2, vec<3, T, Q> const& v3, vec<3, T, Q> const& v4, vec<3, T, Q> const& v5, vec<3, T, Q> const& v6)
		{
			return vec<3, R, Q>(Func(v1.x, v2.x, v3.x, v4.x, v5.x, v6.x), Func(v1.y, v2.y, v3.y, v4.y, v5.x, v6.y), Func(v1.z, v2.z, v3.z, v4.z, v5.z, v6.z));
		}
	};

	template<template<glm::length_t L, typename T, glm::qualifier Q> class vec, typename R, typename T, glm::qualifier Q>
	struct functor6<vec, 4, R, T, Q>
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static vec<4, R, Q> call(R(*Func) (T x, T y, T z, T aa, T ab, T ac), vec<4, T, Q> const& v1, vec<4, T, Q> const& v2, vec<4, T, Q> const& v3, vec<4, T, Q> const& v4, vec<4, T, Q> const& v5, vec<4, T, Q> const& v6)
		{
			return vec<4, R, Q>(Func(v1.x, v2.x, v3.x, v4.x, v5.x, v6.x), Func(v1.y, v2.y, v3.y, v4.y, v5.x, v6.y), Func(v1.z, v2.z, v3.z, v4.z, v5.z, v6.z), Func(v1.w, v2.w, v3.w, v4.w, v5.w, v6.w));
		}
	};
}