#pragma once

//#include <nori/bbox.h>

VR_NAMESPACE_BEGIN

/**
 * \brief Triangle mesh
 *
 * This class stores a triangle mesh object and provides numerous functions
 * for querying the individual triangles. Subclasses of \c Mesh implement
 * the specifics of how to create its contents (e.g. by loading from an
 * external file)
 */
class Mesh {

public:
	
	Mesh() = default;

    /// Release all memory
    virtual ~Mesh() = default;

    /// Return the total number of triangles in this hsape
    uint32_t getTriangleCount() const { return (uint32_t) m_F.cols(); }

    /// Return the total number of vertices in this hsape
    uint32_t getVertexCount() const { return (uint32_t) m_V.cols(); }

    ////// Return an axis-aligned bounding box of the entire mesh
    //const BoundingBox3f &getBoundingBox() const { return m_bbox; }

    ////// Return an axis-aligned bounding box containing the given triangle
    //BoundingBox3f getBoundingBox(uint32_t index) const;

    /// Return a pointer to the vertex positions
    const MatrixXf &getVertexPositions() const { return m_V; }

    /// Return a pointer to the vertex normals (or \c nullptr if there are none)
    const MatrixXf &getVertexNormals() const { return m_N; }

    /// Return a pointer to the texture coordinates (or \c nullptr if there are none)
    const MatrixXf &getVertexTexCoords() const { return m_UV; }

    /// Return a pointer to the triangle vertex index list
    const MatrixXu &getIndices() const { return m_F; }

    /// Return the name of this mesh
    const std::string &getName() const { return m_name; }

    /// Return a human-readable summary of this instance
	std::string toString() const {
		return tfm::format(
			"Mesh[\n"
			"  name = \"%s\",\n"
			"  vertexCount = %i,\n"
			"  triangleCount = %i\n"
			"]",
			m_name,
			m_V.cols(),
			m_F.cols()
		);
	}

   
protected:

protected:
    std::string m_name;                  ///< Identifying name
    MatrixXf      m_V;                   ///< Vertex positions
    MatrixXf      m_N;                   ///< Vertex normals
    MatrixXf      m_UV;                  ///< Vertex texture coordinates
    MatrixXu      m_F;                   ///< Faces
    //BoundingBox3f m_bbox;                ///< Bounding box of the mesh
};

VR_NAMESPACE_END