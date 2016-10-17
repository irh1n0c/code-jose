#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
using namespace std;
template <class T>
class leaf
{
public:
    T valor;
    int grado;
    leaf<T> * padre;
    leaf<T> * hijo[2];
    leaf(T valor)
    {
        this->grado = 1;
        this->valor = valor;
        this->padre = 0;
        this->hijo[0] = 0;
        this->hijo[1] = 0;
    }
};
template <class T>
class AVL
{
public:
    leaf<T> * root;
    string ruta;
    AVL()
    {
        this->ruta = "grafico.dot";
        this->root=0;
    }
    bool encontrar(T valor)
    {
        return encontrar(valor,root);
    }
    bool encontrar(T valor, leaf<T> * aux)
    {
            if(!aux) return 0;
            if(valor==aux->valor) return 1;
            else
            {
                if(valor<aux->valor) return encontrar(valor,aux->hijo[0]);
                return encontrar(valor,aux->hijo[1]);
            }
    }
    leaf<T>* encontrar_2(T valor)
    {
        return encontrar_2(valor,root);
    }
    leaf<T>* encontrar_2(T valor, leaf<T> * aux)
    {
            if(!aux) return 0;
            if(valor==aux->valor) return aux;
            else
            {
                if(valor<aux->valor) return encontrar_2(valor,aux->hijo[0]);
                return encontrar_2(valor,aux->hijo[1]);
            }
    }
    void add(T valor)
	{
		add(valor, root, root);
	}
	void add(T valor, leaf<T> *& m_leaf, leaf<T> * padre)
	{
		if(!m_leaf)
		{
			leaf<T> * nuevo = new leaf<T>(valor);
			nuevo->padre= padre;
            m_leaf = nuevo;
            corregir(m_leaf);
		}
		else
		{
			if(valor==m_leaf->valor) return;
			if(valor<m_leaf->valor)
            {
                add(valor,m_leaf->hijo[0],m_leaf);
            }
			else
            {
                add(valor,m_leaf->hijo[1],m_leaf);
            }
		}
	}
	void corregir(leaf<T> * nodo)
	{
        cout<<nodo->valor<<"||||||||||||||||||||"<<endl;
        if(!nodo) return;
	    if(nodo == root)
        {
            //nodo->color = NEGRO;
            return;
        }
        leaf<T> * bro = hno(nodo); ///bro es el hermano del nodo
        if(bro)
        {
                if(bro->grado==1 && nodo->grado == 1) return;
                else
                {
                    if(abs(nodo->grado-bro->grado)>=2)
                    {
                        equilibrar(nodo);
                        return;

                    }
                    else
                    {
                        nodo->padre->grado++;
                        corregir(nodo->padre);

                    }
                }
        }
        else
        {
            nodo->padre->grado++;
            if(nodo->grado==2)
            {
                cout<<"jijij-------------------"<<endl;
                equilibrar(nodo);
                return;
                cout<<"endjiji--------"<<endl;
            }
            else
            {
                corregir(nodo->padre);
            }
        }
        cout<<":v"<<endl;
        //if(nodo->color==NEGRO) corregir(nodo->padre); /// tal vez no sea necesario

        return;
	}
	void equilibrar(leaf<T> * nodo)
	{
        cout<<nodo->valor<<"<---"<<endl;
        if(nodo->padre->hijo[0]==nodo)
        {
                if(nodo->hijo[0] && nodo->hijo[1])
                {
                    if(nodo->hijo[0]->grado>nodo->hijo[1]->grado)
                    {
                        rotacionDerecha(nodo);
                        verificarGrado(nodo,4);
                    }
                    else
                    {
                        rid(nodo);
                        verificarGrado(nodo,3);
                    }
                }
                else
                {
                    if(!nodo->hijo[0])
                    {
                        rid(nodo);
                        verificarGrado(nodo,2);
                    }
                    else
                    {
                        rotacionDerecha(nodo);
                        verificarGrado(nodo,4);

                    }
                }
        }
        else
        {
                if(nodo->hijo[0] && nodo->hijo[1])
                {
                    if(nodo->hijo[0]->grado>nodo->hijo[1]->grado)
                    {
                            rdi(nodo);
                            verificarGrado(nodo,3);
                    }
                    else
                    {
                            rotacionIzquierda(nodo);
                            verificarGrado(nodo,1);
                    }
                }
                else
                {
                    if(!nodo->hijo[0])
                    {
                        rotacionIzquierda(nodo);
                        verificarGrado(nodo,1);
                    }
                    else
                    {
                        cout<<"here"<<endl;
                        cout<<nodo->valor<<endl;
                        rdi(nodo);
                        cout<<nodo->valor<<endl;
                        cout<<"sds"<<endl;
                        verificarGrado(nodo,3);
                        cout<<"mimimmiau"<<endl;
                    }
                }
        }
	}
	/// rii 1 rid 2 rdi 3 rdd 4
	void verificarGrado(leaf<T> * nodo,int var)
	{

        cout<<"dfsfsd"<<endl;
        cout<<nodo->valor<<endl;
        //if(!nodo) return;
	    switch(var)
	    {
            case 1:
                cout<<"sdfsd123";
                nodo->hijo[0]->grado-=2;
            case 2:
                nodo->padre->grado++;
                nodo->padre->hijo[1]->grado-=2;
            case 3:
                cout<<"dsa"<<endl;
                nodo->padre->grado++;
                nodo->padre->hijo[0]->grado-=2;
                break;
            case 4:
                nodo->hijo[1]->grado-=2;
	    }


        //if(!nodo->padre) corregir(nodo);
        //corregir(nodo->padre);

	}
	///pos es la posicion del padre segun el abuelo
	/// 1 si esta a la derecha del abuelo
	/// 0 si esta a la izquiera del abuelo
	void rotacionDerecha(leaf<T> * nodo)
	{

        if(nodo->padre->padre)
        {
            if(nodo->padre->padre->hijo[0]==nodo->padre)    nodo->padre->padre->hijo[0]=nodo;
            else    nodo->padre->padre->hijo[1]=nodo;
            nodo->padre->hijo[0]= nodo->hijo[1];
            nodo->hijo[1]=nodo->padre;
            nodo->padre=nodo->padre->padre;
            nodo->hijo[1]->padre=nodo;
        }

        else
        {

            root = nodo;
            nodo->padre->hijo[0]= nodo->hijo[1];
            nodo->hijo[1]=nodo->padre;
            nodo->padre=0;
            nodo->hijo[1]->padre=nodo;
        }


	}
	void rotacionIzquierda(leaf<T> * nodo)
	{
	    if(nodo->padre->padre)
        {
            if(nodo->padre->padre->hijo[0]==nodo->padre)    nodo->padre->padre->hijo[0]=nodo;
            else    nodo->padre->padre->hijo[1]=nodo;
            nodo->padre->hijo[1]= nodo->hijo[0];
            nodo->hijo[0]=nodo->padre;
            nodo->padre=nodo->padre->padre;
            nodo->hijo[0]->padre=nodo;

        }
        else
        {
            root = nodo;
            nodo->padre->hijo[1]= nodo->hijo[0];
            nodo->hijo[0]=nodo->padre;
            nodo->padre=0;
            nodo->hijo[0]->padre=nodo;
        }

	}
	void rid(leaf<T> * nodo)
	{
	    leaf<T> * aux1 = nodo->padre;
        leaf<T> * aux2 = nodo->hijo[1];
        if(nodo->hijo[1]->hijo[0] && nodo->hijo[1]->hijo[1])
        {
            leaf<T> * aux3 = nodo->hijo[1]->hijo[1];
            leaf<T> * aux4 = nodo->hijo[1]->hijo[0];
            if(nodo->padre->padre)
            {
                leaf<T> * aux5 = nodo->padre->padre;
                aux2->padre=aux5;
                if(nodo->padre->padre->hijo[0]==nodo->padre)   aux5->hijo[0] = aux2;
                else    aux5->hijo[1] = aux2;


            }
            else
            {
                aux2->padre=0;
            }

                aux2->hijo[1]=aux1;
                aux2->hijo[0]=nodo;
                aux1->padre= aux2;
                nodo->padre= aux2;
                aux1->hijo[0]=aux3;
                aux3->padre=aux1;
                nodo->hijo[1]=aux4;
                aux4->padre=nodo;


        }
        else
        {

            if(!nodo->hijo[1]->hijo[0])
            {
                leaf<T> * aux3 = nodo->hijo[1]->hijo[1];
                if(nodo->padre->padre)
                {
                    leaf<T> * aux5 = nodo->padre->padre;
                    aux2->padre=aux5;
                    if(nodo->padre->padre->hijo[0]==nodo->padre)   aux5->hijo[0] = aux2;
                    else    aux5->hijo[1] = aux2;


                }
                else
                {
                    aux2->padre=0;
                }

                    aux2->hijo[1]=aux1;
                    aux2->hijo[0]=nodo;
                    aux1->padre= aux2;
                    nodo->padre= aux2;
                    aux1->hijo[0]=aux3;
                    aux3->padre=aux1;
            }
            if(nodo->hijo[1]->hijo[0])
            {
                if(!nodo->hijo[1]->hijo[0])
                {
                    leaf<T> * aux4 = nodo->hijo[1]->hijo[0];
                    if(nodo->padre->padre)
                    {
                        leaf<T> * aux5 = nodo->padre->padre;
                        aux2->padre=aux5;
                        if(nodo->padre->padre->hijo[0]==nodo->padre)   aux5->hijo[0] = aux2;
                        else    aux5->hijo[1] = aux2;


                    }
                    else
                    {
                        aux2->padre=0;
                    }

                        aux2->hijo[1]=aux1;
                        aux2->hijo[0]=nodo;
                        aux1->padre= aux2;
                        nodo->padre= aux2;
                        nodo->hijo[1]=aux4;
                        aux4->padre=nodo;

                }

            }
            else
            {
                if(nodo->padre->padre)
                {
                    leaf<T> * aux5 = nodo->padre->padre;
                    aux2->padre=aux5;
                    if(nodo->padre->padre->hijo[0]==nodo->padre)   aux5->hijo[0] = aux2;
                    else    aux5->hijo[1] = aux2;
                }
                else
                {
                    aux2->padre=0;
                }


                aux2->hijo[0]=aux1;
                aux2->hijo[1]=nodo;
                aux1->padre= aux2;
                nodo->padre= aux2;
            }



    }

	}
	void rdi(leaf<T> * nodo)
	{
        cout<<"jeje"<<endl;
	    leaf<T> * aux1 = nodo->padre;
        leaf<T> * aux2 = nodo->hijo[0];
        if(nodo->hijo[0]->hijo[0] && nodo->hijo[0]->hijo[1])
        {
            leaf<T> * aux3 = nodo->hijo[0]->hijo[0];
            leaf<T> * aux4 = nodo->hijo[0]->hijo[1];
            if(nodo->padre->padre)
            {
                leaf<T> * aux5 = nodo->padre->padre;
                aux2->padre=aux5;
                if(nodo->padre->padre->hijo[0]==nodo->padre)   aux5->hijo[0] = aux2;
                else    aux5->hijo[1] = aux2;
            }
            else
            {
                root=aux2;
                aux2->padre=0;
            }


            aux2->hijo[0]=aux1;
            aux2->hijo[1]=nodo;
            aux1->padre= aux2;
            nodo->padre= aux2;

            aux1->hijo[1]=aux3;
            aux3->padre=aux1;
            nodo->hijo[0]=aux4;
            aux4->padre=nodo;

        }
        else
        {

            if(nodo->hijo[0]->hijo[1])
            {
                leaf<T> * aux4 = nodo->hijo[0]->hijo[1];
                if(nodo->padre->padre)
                {
                    leaf<T> * aux5 = nodo->padre->padre;
                    aux2->padre=aux5;
                    if(nodo->padre->padre->hijo[0]==nodo->padre)   aux5->hijo[0] = aux2;
                    else    aux5->hijo[1] = aux2;
                }
                else
                {
                    this->root= aux2;
                    aux2->padre=0;
                }


                aux2->hijo[0]=aux1;
                aux2->hijo[1]=nodo;
                aux1->padre= aux2;
                nodo->padre= aux2;
                nodo->hijo[0]=aux4;
                aux4->padre=nodo;
            }
            if(nodo->hijo[0]->hijo[0])
            {
                leaf<T> * aux3 = nodo->hijo[0]->hijo[0];
                if(nodo->padre->padre)
                {
                    leaf<T> * aux5 = nodo->padre->padre;
                    aux2->padre=aux5;
                    if(nodo->padre->padre->hijo[0]==nodo->padre)   aux5->hijo[0] = aux2;
                    else    aux5->hijo[1] = aux2;
                }
                else
                {
                    this->root=aux2;
                    aux2->padre=0;
                }


                aux2->hijo[0]=aux1;
                aux2->hijo[1]=nodo;
                aux1->padre= aux2;
                nodo->padre= aux2;
                aux1->hijo[1]=aux3;
                aux3->padre=aux1;
            }
            else
            {
                cout<<"aqui"<<endl;
                cout<<nodo->valor<<endl;
                cout<<nodo->padre->valor<<endl;
                if(nodo->padre->padre)
                {
                    cout<<nodo->valor<<endl;
                    leaf<T> * aux5 = nodo->padre->padre;
                    aux2->padre=aux5;
                    if(nodo->padre->padre->hijo[0]==nodo->padre)   aux5->hijo[0] = aux2;
                    else    aux5->hijo[1] = aux2;

                    aux2->hijo[0]=aux1;
                    aux2->hijo[1]=nodo;
                    aux1->padre= aux2;
                    nodo->padre= aux2;
                }
                else
                {

                    cout<<nodo->valor<<"<-"<<endl;
                    cout<<aux2->valor<<endl;
                    aux2->hijo[0]=aux1;
                    aux2->hijo[1]=nodo;
                    aux1->padre= aux2;
                    nodo->padre= aux2;
                    aux2->padre=0;
                    root= aux2;
                    cout<<aux2->valor<<endl;
                    cout<<nodo->valor<<"<-|||"<<endl;
                }
                cout<<nodo->valor<<"<----"<<endl;


                cout<<nodo->valor<<endl;

            }


        }
        cout<<nodo->valor<<endl;
	}
	leaf<T> * tio(leaf<T> * nodo)
	{
        if(nodo->padre->padre->hijo[0]== nodo->padre)
            return nodo->padre->padre->hijo[1];
        return nodo->padre->padre->hijo[0];
	}
	leaf<T> * hno(leaf<T> * nodo)
	{
        if(nodo->padre->hijo[0]== nodo)
            return nodo->padre->hijo[1];
        return nodo->padre->hijo[0];
	}
	void graficar()
	{
        ofstream * fichero = new ofstream (this->ruta);
        *fichero<<"digraph G {"<<endl;
        print(root,fichero);
        *fichero<<"}";
        fichero->close();

	}
	void print(leaf<T> * aux, ofstream * archivo)
	{
	    if(!aux)return;

	    if(aux->hijo[0])
        {
            *archivo<<aux->valor<<"->"<<aux->hijo[0]->valor<<endl;
            print(aux->hijo[0],archivo);
	    }
	    if(aux->hijo[1] )
	    {
	        *archivo<<aux->valor<<"->"<<aux->hijo[1]->valor<<endl;
	        print(aux->hijo[1],archivo);
	    }
	    //if(!aux->color) *archivo<<aux->valor<<" [color=black,style=filled,fontcolor=white];"<<endl;
        //else *archivo<<aux->valor<<" [color=red,style=filled,fontcolor=white];"<<endl;





	}

};

int main()
{
    AVL<int> nuevo;
    nuevo.add(10);
    nuevo.add(15);
    nuevo.add(13);
    //nuevo.graficar();
    return 0;
}

