#include"Sprites.h"
#include<memory>

        
std::vector<Sprite *> Sprite::List;
int Sprite::Count = 0;

// UVBuffer     *TileMap::UVCoords;
// VertexBuffer *TileMap::Vertices;
// IndexBuffer  *TileMap::Indices;
// 
// std::vector<Vec2>   TileMap::UVBatch;
// std::vector<Vec3>   TileMap::VertexBatch;
// std::vector<GLuint> TileMap::IndexBatch;

//=========================================================================================================================================
//_______________________________________  Frame Class ____________________________________________________________________________________
//                                                                                                                                  
//Each Frame is a UV buffer whos Index is Bound prior to rendering in accordance with the current timestep for the Animated Sprite
//=========================================================================================================================================
// I suppose I could also store the Frame Data linearly here and
// Offset to the frame that I wish to render from
// That might be the best method honestly.

Frame::Frame(Image *img, Quad f)
{
    float UnitX = (1.0f / img->Width);
    float UnitY = (1.0f / img->Height);

    Coords[0] = Vec2((float)f.x * UnitX + (float)f.Width * UnitX, (float)f.y * UnitY + (float)f.Height * UnitY);
    Coords[1] = Vec2((float)f.x * UnitX , (float)f.y * UnitY + (float)f.Height * UnitY);
    Coords[2] = Vec2((float)f.x * UnitX , (float)f.y * UnitY);
    Coords[3] = Vec2((float)f.x * UnitX + (float)f.Width * UnitX, (float)f.y * UnitY);

    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vec2) * 4 , Coords, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void Frame::Bind()
{
      glBindBuffer(GL_ARRAY_BUFFER, ID);      
        glTexCoordPointer(2, GL_FLOAT, 0, (char *) NULL);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}
void Frame::Unbind()
{
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER,0);
}

//=========================================================================================================================================
//_______________________________________  State Class ____________________________________________________________________________________
//                                                                                                                                  
//   Each State is a state that an Entity can be in, Dead alive etc and is a group of frames that represents a state of the StaticSprite
//=========================================================================================================================================

State::State(Image *img, Quad srcrect, GLuint numframes)
     :TotalFrames(numframes)
{
    CurrentFrame = 0;
    Frames.reserve(numframes);
    GLuint x = srcrect.x;
    for_loop(Count, numframes)
    {
        Quad  Source(x, srcrect.y, srcrect.Width, srcrect.Height);
        Frame frame(img, Source);
        x += srcrect.Width;
       *this += frame;
    }
}
std::vector<Frame> &State::AddFrame(Frame frame)
{
	Frames.emplace_back(frame);
	return Frames;
} // Adds a frame to the State

//=========================================================================================================================================
//_______________________________________  Sprite Class ___________________________________________________________________________________
//                                                                                                                                  
// Sprite is a Collection of States which can be Enumerated or Defined so Various Animations can play our in accordance with Gameplay
//=========================================================================================================================================

Sprite::Sprite(char *name, Image *source, int numstates)
      : NumberofStates(numstates), 
        ID(Count++),   
        Name(name),
        Scale(Vec2(1)),
        CurrentState(0),
        AnimationSpeed(150),
        Picture(source),
        Position(Vec2(0))
{     
    Lifetime = glfwGetTime() * 1000;
    States.reserve(numstates);
    
    for_loop(count, NumberofStates)
    {
        State temp;
        States.emplace_back(temp);
    }

    Vec3 VertexData[] = 
    {
         Vec3(0,0,0),
         Vec3(Picture->Width, 0, 0),
         Vec3(Picture->Width, Picture->Height,0),
         Vec3(0,Picture->Height, 0), 
    };

    GLuint IndexData[] = 
    {
        2,3,1,  0,1,3,
    };

    Vertices = new VertexBuffer(  &VertexData[0], 4); 
    Indices =  new IndexBuffer(   &IndexData[0], 6);

    List.push_back(this);
}
void Sprite::Render()
{
    GLuint ticks = (glfwGetTime() * 1000) - Lifetime;
    int CF = (ticks / AnimationSpeed) % States[CurrentState].TotalFrames;

    glPushMatrix();
    Picture->Bind();
        glTranslatef(Position.x, Position.y, 0.0f);
        glScalef(Scale.x, Scale.y,0.0f);
        Vertices->Bind();
            Indices->Bind();
                States[CurrentState].Frames[CF].Bind();
                     glDrawElements(GL_TRIANGLES, Indices->ElementCount , GL_UNSIGNED_INT, nullptr);
                States[CurrentState].Frames[CF].Bind();
            Indices->Unbind();
        Vertices->Unbind();
    Picture->Unbind();
    glPopMatrix();
}

void Sprite::Update()
{
    ModelMatrix = glm::mat4(1.0f); // Set Identity and Rotate all axis followed with the Translation.
    ModelMatrix = glm::translate(ModelMatrix, Vec3(Position.x, Position.y, 0.0f)); 
}


// I could also probably change the Data in the UV buffer every frame update to reflect the correct position in the
// Image used to render from by providing a new Source rect everytime.

/*=================================================================================================================================
                                                     TILE MAP                                                                         
About: Loads a BMP and cuts it into tiles per specifications; After these Tiles can be Spawned, Positioned and eventially
Rotated all being called when the Appropriate Render() command is called for this Tilemap.
==================================================================================================================================*/
TileMap::TileMap(Image *img, Quad f)
{
    BorderX = 0;
    BorderY = 0;
    
          UVCount     = 0;
          IndexCount  = 0;
          VertexCount = 0;

    FullMap = img;
    int StrideX = f.Width,
        StrideY = f.Height;

    for(int Ypos = 0; Ypos < img->Height; Ypos += StrideY)
    {
        for(int Xpos = 0; Xpos < img->Width; Xpos += StrideX)
        {
            Quad Block(Xpos, Ypos, f.Width, f.Height);
            Tile *temp = new Tile(this, Block);
            Tiles.push_back(temp);
        }
    }


    Vec3   *Vdata  = new Vec3(0);
    Vec2   *UVData = new Vec2(0);
    GLuint *IData  = new GLuint(0);
    Vertices = new VertexBuffer(Vdata,1);
    UVCoords = new UVBuffer(UVData,1);
    Indices  = new IndexBuffer(IData,1);
}

void TileMap::BatchUpdate()
{
    int VCounter = 0;
    VertexBatch.clear();

    for(auto &T: BatchedTiles)
    {
        for_loop(VIndex, T->Vertices->ElementCount)
        {
            VertexBatch.push_back(T->Vertices->Data[VIndex] + Vec3(T->Position.x, T->Position.y, 0));
        }
        VCounter += T->Vertices->ElementCount;
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, Vertices->ID);
        glBufferData(GL_ARRAY_BUFFER, VCounter * sizeof(Vec3), &VertexBatch[0], GL_DYNAMIC_DRAW) ; 
}

void TileMap::Render()
{
    glPushMatrix();
        FullMap->Bind();
            UVCoords->Bind();
                Vertices->Bind();
                    Indices->Bind();
                        glDrawElements(GL_TRIANGLES, Indices->ElementCount , GL_UNSIGNED_INT, nullptr);
   glPopMatrix();
}
void TileMap::DestroyTile(GLuint tileindex)
{
    BatchedTiles.erase(BatchedTiles.begin() + tileindex);
    UVBatch.clear();
    IndexBatch.clear();
    VertexBatch.clear();

    GLuint Stepper = 0;
    for(auto &T: BatchedTiles)
    {
        for_loop(Counter, T->UVCoords->ElementCount)
        {
            VertexBatch.push_back(T->Vertices->Data[Counter] + Vec3(T->Position.x, T->Position.y, 0));
            UVBatch.push_back(T->UVCoords->Data[Counter]);
        }
        for_loop(Counter, T->Indices->ElementCount)
        {
            IndexBatch.push_back(T->Indices->Data[Counter] + Stepper);
        }
        Stepper += T->UVCoords->ElementCount;
    }

    glBindBuffer(GL_ARRAY_BUFFER, Vertices->ID);
    Vertices->ElementCount = VertexCount;
        glBufferData(GL_ARRAY_BUFFER, VertexCount * sizeof(Vec3), &VertexBatch[0], GL_DYNAMIC_DRAW) ; 

    glBindBuffer(GL_ARRAY_BUFFER, UVCoords->ID); // Update UVBuffer
    UVCoords->ElementCount = VertexCount;
        glBufferData(GL_ARRAY_BUFFER, VertexCount * sizeof(Vec2),  &UVBatch[0], GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,Indices->ID); // Update IndexBuffer
    Indices->ElementCount = IndexCount;
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndexCount * sizeof(GLuint), &IndexBatch[0], GL_DYNAMIC_DRAW);
}
int  TileMap::SpawnTile(Vec2 pos, GLuint tileindex)
{
    Tile *PushTile =  new Tile(*Tiles[tileindex]);
          PushTile->Position = pos;

    for_loop(Counter, PushTile->Indices->ElementCount)
    {
        IndexBatch.push_back(PushTile->Indices->Data[Counter] + VertexCount);
    }
    for_loop(Counter, PushTile->UVCoords->ElementCount)
    {
        UVBatch.push_back(PushTile->UVCoords->Data[Counter]);
    }
    
    UVCount     += PushTile->UVCoords->ElementCount;
    IndexCount  += PushTile->Indices->ElementCount;
    VertexCount += PushTile->Vertices->ElementCount;
    
    BatchedTiles.push_back(PushTile);
    
    glBindBuffer(GL_ARRAY_BUFFER, UVCoords->ID); // Update UVBuffer
    UVCoords->ElementCount = VertexCount;
        glBufferData(GL_ARRAY_BUFFER, VertexCount * sizeof(Vec2),  &UVBatch[0], GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,Indices->ID); // Update IndexBuffer
    Indices->ElementCount = IndexCount;
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndexCount * sizeof(GLuint), &IndexBatch[0], GL_DYNAMIC_DRAW);

  return BatchedTiles.size();
}






/*=================================================================================================================================
                                                     TILE CLASS                                                                         
                                                   --------------                                         
About: TILE Class contains the Scale Position and Rotation of an Individual tile extracted out of a Tilemap. Given an ID according 
   to its Creation Order.
==================================================================================================================================*/


Tile::Tile(TileMap* source, Quad area)
    : Scale(Vec2(1)),
      Position(Vec2(0))
{
    Size.x = area.Width;
    Size.y = area.Height;

    Vec3 VertexData[] = 
    {
         Vec3(0,0,0),
         Vec3(area.Width, 0, 0),
         Vec3(area.Width, area.Height,0),
         Vec3(0, area.Height, 0), 
    };

    GLuint IndexData[] = 
    {
        2,3,1,  0,1,3,
    };

    float UnitX = (1.0f / source->FullMap->Width);
    float UnitY = (1.0f / source->FullMap->Height);

    Vec2 Coords[4];
         Coords[0] = Vec2((float)area.x * UnitX + (float)area.Width * UnitX, (float)area.y * UnitY + (float)area.Height * UnitY);
         Coords[1] = Vec2((float)area.x * UnitX , (float)area.y * UnitY + (float)area.Height * UnitY);
         Coords[2] = Vec2((float)area.x * UnitX , (float)area.y * UnitY);
         Coords[3] = Vec2((float)area.x * UnitX + (float)area.Width * UnitX, (float)area.y * UnitY);

    Picture = source->FullMap;
    Position = Vec2(100);
    Vertices = new VertexBuffer( &VertexData[0], 4); 
    Indices =  new IndexBuffer( &IndexData[0], 6);
    UVCoords = new UVBuffer(&Coords[0],4); 
}
void Tile::Render()
{

    glPushMatrix();
    Picture->Bind();
        glTranslatef(Position.x, Position.y, 0.0f);
       // glScalef(Scale.x, Scale.y,0.0f);
        UVCoords->Bind();
        Vertices->Bind();
            Indices->Bind();
                glDrawElements(GL_TRIANGLES, Indices->ElementCount , GL_UNSIGNED_INT, nullptr);
            Indices->Unbind();
        Vertices->Unbind();
    Picture->Unbind();
    glPopMatrix();
}
void Tile::Render(Vec2 pos)
{

    glPushMatrix();
    Picture->Bind();
        glTranslatef(pos.x, pos.y, 0.0f);
       // glScalef(Scale.x, Scale.y,0.0f);
        UVCoords->Bind();
        Vertices->Bind();
            Indices->Bind();
                glDrawElements(GL_TRIANGLES, Indices->ElementCount , GL_UNSIGNED_INT, nullptr);
            Indices->Unbind();
        Vertices->Unbind();
    Picture->Unbind();
    glPopMatrix();
}


//int x1 =  area.x * UnitX;
//int y1 =  area.y * UnitY;
//int x2 = (area.x * UnitX) + (source->FullMap->Width  * UnitX);
//int y2 = (area.y * UnitY) + (source->FullMap->Height * UnitY);
//
//
//void BatchRender::Submit(Block *object)
//{
//    if(object->Vertices->ID < FirstObject) FirstObject = object->Vertices->ID;
//    
//    ObjectCount++;
//
//    PositionBuffers.push_back(object->Position);
//
//    std::vector<Vec3> TransformedVerts;
//    std::vector<GLuint> TransformedIndices;
//    std::vector<Vec2> TransformedUV;
//
//    for_loop(Index, 24)
//    {
//        TransformedVerts.push_back(object->VertexList[Index] + object->Position);
//    }
//
//    for_loop(Index, 36)
//    {
//        TransformedIndices.push_back(object->IndexList[Index] + VertexCount);
//    }
//
//    IndexBuffers.insert(  IndexBuffers.end(),    TransformedIndices.begin(),     TransformedIndices.end());
//    VertexBuffers.insert( VertexBuffers.end(),  TransformedVerts.begin(),    TransformedVerts.end());
//    TextureBuffers.insert(TextureBuffers.end(), object->TextureCoords.begin(), object->TextureCoords.end());
//  
//    VertexCount  += 24;
//    IndexCount += 36;
//}
//void BatchRender::Build()
//{
//    Vertices = new VertexBuffer  (&VertexBuffers[0], VertexCount);
//    Indices  = new IndexBuffer   (&IndexBuffers[0], IndexCount);
//    Textures = new TextureBuffer (*BatchTexture, &TextureBuffers[0], VertexCount);
//}
//
//
//