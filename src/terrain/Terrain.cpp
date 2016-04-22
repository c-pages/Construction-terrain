#include "terrain/Terrain.h"
#include "../noiseutils.h"

#include "stdio.h"

Terrain::Terrain( sf::Vector2i taille  )
: m_tailleCarte     ( taille )
, m_couleurTerre    ( sf::Color (100,100,100))
, m_couleurSol      ( sf::Color (201,202,158))
{
    // creer le terrain a partir du perlinpinpin
    creer();

    // les shaders
    m_shaderFlou.loadFromFile( "media/shaders/flou.frag" , sf::Shader::Fragment );
    m_shaderFlou.setParameter( "texture", sf::Shader::CurrentTexture );
    m_shaderFlou.setParameter( "blur_radius", 0.005f );

    m_shaderHachures.loadFromFile( "media/shaders/hachures&contours.frag" , sf::Shader::Fragment );
    m_shaderHachures.setParameter( "texture", sf::Shader::CurrentTexture );

    m_shaderGrille.loadFromFile( "media/shaders/grille.frag" , sf::Shader::Fragment );
//    m_shaderGrille.setParameter( "texture", sf::Shader::CurrentTexture );

    // les textures
    m_shapeTerre.setTexture( m_textureTerre );
    m_shapeOmbreTerre.setTexture( m_textureTerre );

}

Terrain::~Terrain()
{
    //dtor
}

void Terrain::creer()
{


    // le shape
    m_shapeTerre.setSize ( { m_tailleCarte.x, m_tailleCarte.y } );

    m_shapeOmbreTerre.setSize ( { m_tailleCarte.x, m_tailleCarte.y } );
    m_shapeOmbreTerre.setPosition (3,3);
    m_shapeOmbreTerre.setFillColor( sf::Color (0,0,0,150));

    m_shapesol.setSize ( { m_tailleCarte.x, m_tailleCarte.y } );
    m_shapesol.setFillColor( m_couleurSol );

    // creation de l'image qui va servir à creer le noise
    // ( on pourra changer la maniere de le faire en accedant directement à la valeur dans le noise sans le dessiner dans un fichier )
    sf::Image* image = noise::creerPerlinImage( m_tailleCarte
                                               , 9          // octaves
                                               , 1          // frequence
                                               , .5 );      // persistence
//    image->saveToFile( "turlututu.jpg");

    // Dessiner la map avec rond ?!?
    int ecartMin = 10;

    m_renderTexture.create(m_tailleCarte.x, m_tailleCarte.y );
    m_renderTexture.clear(sf::Color::Transparent);

    // ondessine les rond sur le renderTexture en fonction de la map de perlin
    for ( unsigned int y = 0; y<image->getSize().y; y+= ecartMin  )
        for ( unsigned int x = 0; x<image->getSize().x; x+= ecartMin )
            if ( image->getPixel(x,y).r< 75  )
            {
                int rayon =  rand()% 20 + ecartMin;
                sf::CircleShape cercle ( rayon );
                cercle.setPosition( x, y);
                cercle.setFillColor( m_couleurTerre );

                m_renderTexture.draw(cercle);
            }


    m_renderTexture.display();
    m_textureTerre = &m_renderTexture.getTexture();

}
void Terrain::update()
{

}
void Terrain::draw (sf::RenderTarget& target, sf::RenderStates states) const
{
    // le sol
    states.shader = &m_shaderGrille;
    target.draw ( m_shapesol , states );

    // l'ombre de la terre
    states.shader = &m_shaderFlou;
    target.draw ( m_shapeOmbreTerre , states );

    // la terre
    states.shader = &m_shaderHachures;
    target.draw ( m_shapeTerre , states );
}
