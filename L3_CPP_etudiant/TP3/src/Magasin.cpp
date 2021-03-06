#include "Magasin.hpp"
#include "Client.hpp"
#include "Produit.hpp"
#include "Location.hpp"
#include <algorithm>

Magasin::Magasin(){
  _idCourantClient = 0;
  _idCourantProduit = 0;
}

int Magasin::nbClients() const {

  return _clients.size();
}

void Magasin::ajouterClient(const std::string & nom){
  Client c(_idCourantClient, nom);
  _clients.push_back(c);
  _idCourantClient = _idCourantClient + 1;
}

void Magasin::afficherClients() const {
  for (int i=0; i < _clients.size(); i++){
    std::cout << _clients[i].getNom() << std::endl;
  }
}

void Magasin::supprimerClient(int idClient){
  try{
    for (int i=0; i < _clients.size(); i++){
      if(idClient == _clients[i].getId()){
	std::swap(_clients.back(), _clients[i]);
	_clients.pop_back();
	return;
      }
    }
    throw std::string("Le client n existe pas!");
  }catch(std::string const& chaine)
    {
      std::cerr << chaine << std::endl;
    }
  }

int Magasin::nbProduits() const {

  return _produits.size();
}

void Magasin::ajouterProduit(const std::string & nom){
  Produit p(_idCourantProduit + 1, nom);
  _produits.push_back(p);
  _idCourantProduit = _idCourantProduit + 1;
}

void Magasin::afficherProduits() const {
  for (int i=0; i < _produits.size(); i++){
    std::cout << _produits[i].getDescription() << std::endl;
  }
}

void Magasin::supprimerProduit(int idProduit){
  try{
    for (int i=0; i < _produits.size(); i++){
      if(idProduit == _produits[i].getId()){
	std::swap(_produits.back(), _produits[i]);
	_produits.pop_back();
	return;
      }
    }
  throw std::string("Le produit n existe pas!");
  }catch(std::string const& chaine)
    {
      std::cerr << chaine << std::endl;
    }
}

int Magasin::nbLocations() const {

  return _locations.size();
}

void Magasin::ajouterLocation(int idClient, int idProduit){
  Location l{idClient, idProduit};
  _locations.push_back(l);
}

void Magasin::afficherLocations() const {
  for (int i=0; i < _locations.size(); i++){
     _locations[i].afficherLocation();
  }
}

void Magasin::supprimerLocation(int idClient,int idProduit){
  try{
    for (int i=0; i < _locations.size(); i++){
      if(idProduit == _locations[i]._idProduit && idClient == _locations[i]._idClient){
	std::swap(_locations.back(), _locations[i]);
	_locations.pop_back();
	return;
      }
    }
  throw std::string("La location n existe pas!");
  }catch(std::string const& chaine)
    {
      std::cerr << chaine << std::endl;
    }
}

bool Magasin::trouverClientDansLocation(int idClient) const {

  for(int i=0; i < _locations.size(); i++){
    if(_locations[i]._idClient == idClient){
      return true;
    }
  }
  return false;
}

std::vector<int> Magasin::calculerClientsLibres() const {
  std::vector<int> VectorReturned;

  for(int i=0; i < _clients.size(); i++){
    for(int j=0; j < _locations.size(); j++){
      if(_clients[i].getId() != _locations[j]._idClient){
	VectorReturned.push_back(_clients[i].getId());
      }
    }
  }

  return VectorReturned;
}

bool Magasin::trouverProduitDansLocation(int idProduit) const {

  for(int i=0; i < _locations.size(); i++){
    if(_locations[i]._idProduit == idProduit){
      return true;
    }
  }
}

std::vector<int> Magasin::calculerProduitsLibres() const {
  std::vector<int> VectorReturned;

  for(int i=0; i < _produits.size(); i++){
    for(int j=0; j < _locations.size(); j++){
      if(_produits[i].getId() != _locations[j]._idProduit){
	VectorReturned.push_back(_produits[i].getId());
      }
    }
  }

  return VectorReturned;
}
