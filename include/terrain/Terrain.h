#ifndef TERRAIN_H
#define TERRAIN_H

#include <SFML/Graphics.hpp>

class Terrain: public sf::Drawable, public sf::Transformable
{
public:
    Terrain( sf::Vector2i taille );
    virtual ~Terrain();

    void creer();
    void update();
    void draw (sf::RenderTarget& target, sf::RenderStates states) const;

protected:

private:

    sf::Vector2i            m_tailleCarte;      ///< la taille du terrain
    sf::RenderTexture       m_renderTexture;    ///< le render ou dessiner la map
    sf::Color               m_couleurTerre;
    sf::Color               m_couleurSol;

    sf::Image               m_image;            ///< la bitmap dessinée
    const sf::Texture*      m_textureTerre;          ///< la texture
//    const sf::Texture*      m_textureTerre;          ///< la texture

    sf::RectangleShape      m_shapeTerre;            ///< le shape qui recoit le terrain
    sf::RectangleShape      m_shapeOmbreTerre;            ///< le shape qui recoit le terrain
    sf::RectangleShape      m_shapesol;            ///< le shape qui recoit le terrain

    sf::Shader              m_shaderFlou;
    sf::Shader              m_shaderHachures;
    sf::Shader              m_shaderGrille;
};

#endif // TERRAIN_H
