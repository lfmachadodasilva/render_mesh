/**
* Modulo de definicao da classe COLLISION_CONTACT_PAIR.Esta classe define a estrutura de dados
* responsavel por retornar os pares de contato entre duas hierarquias de colisao
*/

#ifndef __COLLISION_CONTACT_PAIR_H__
#define __COLLISION_CONTACT_PAIR_H__

#include "../array/array.h"

class COLLISION_CONTACT_PAIR
{

  public:

    class PAIR_DATA
    {
      public:

      // o identificador do objeto A
      int Object_A_ID;

      // o identificador do objeto B
      int Object_B_ID;

      // Teste As coordendas do triangulo A
      // As coordendas do triangulo B
      float Tri_A_V0[3];
      float Tri_A_V1[3];
      float Tri_A_V2[3];

      float Tri_B_V0[3];
      float Tri_B_V1[3];
      float Tri_B_V2[3];

      /**
      * A distancia de penetracao. E util para o calculo de raio contra triangulo,
      * ja que ira guardar a profundidade (t) do raio
      */
      float Depth;

      PAIR_DATA(void)
      {
        this->Object_A_ID = -1;
        this->Object_B_ID = -1;

        this->Tri_A_V0[0] = this->Tri_A_V0[1] = this->Tri_A_V0[2] = 0.0f;
        this->Tri_A_V1[0] = this->Tri_A_V1[1] = this->Tri_A_V1[2] = 0.0f;
        this->Tri_A_V2[0] = this->Tri_A_V2[1] = this->Tri_A_V2[2] = 0.0f;

        this->Tri_B_V0[0] = this->Tri_B_V0[1] = this->Tri_B_V0[2] = 0.0f;
        this->Tri_B_V1[0] = this->Tri_B_V1[1] = this->Tri_B_V1[2] = 0.0f;
        this->Tri_B_V2[0] = this->Tri_B_V2[1] = this->Tri_B_V2[2] = 0.0f;

        this->Depth = -1.0f;
      }

      ~PAIR_DATA(void)
      {
      }

      PAIR_DATA operator = (const PAIR_DATA& Contact)
      {
        this->Object_A_ID = Contact.Object_A_ID;
        this->Object_B_ID = Contact.Object_B_ID;

        this->Tri_A_V0[0] = Contact.Tri_A_V0[0];
        this->Tri_A_V0[1] = Contact.Tri_A_V0[1];
        this->Tri_A_V0[2] = Contact.Tri_A_V0[2];

        this->Tri_A_V1[0] = Contact.Tri_A_V1[0];
        this->Tri_A_V1[1] = Contact.Tri_A_V1[1];
        this->Tri_A_V1[2] = Contact.Tri_A_V1[2];

        this->Tri_A_V2[0] = Contact.Tri_A_V2[0];
        this->Tri_A_V2[1] = Contact.Tri_A_V2[1];
        this->Tri_A_V2[2] = Contact.Tri_A_V2[2];

        this->Tri_B_V0[0] = Contact.Tri_B_V0[0];
        this->Tri_B_V0[1] = Contact.Tri_B_V0[1];
        this->Tri_B_V0[2] = Contact.Tri_B_V0[2];

        this->Tri_B_V1[0] = Contact.Tri_B_V1[0];
        this->Tri_B_V1[1] = Contact.Tri_B_V1[1];
        this->Tri_B_V1[2] = Contact.Tri_B_V1[2];

        this->Tri_B_V2[0] = Contact.Tri_B_V2[0];
        this->Tri_B_V2[1] = Contact.Tri_B_V2[1];
        this->Tri_B_V2[2] = Contact.Tri_B_V2[2];
        this->Depth = Contact.Depth;

        return(*this);
      }
    };

  public:
   
    /*
    * Array de Pair_Data
    */
    ARRAY<PAIR_DATA> Contact_Pairs;
    
    COLLISION_CONTACT_PAIR(void)
    {
    }

    ~COLLISION_CONTACT_PAIR(void)
    {
      Contact_Pairs.Destroy();
    }
};
#endif

