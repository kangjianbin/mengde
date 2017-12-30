#ifndef DEPLOY_VIEW_H_
#define DEPLOY_VIEW_H_

#include "composite_view.h"
#include "callback_view.h"

class Hero;
class IDeployHelper;
class TextView;

class HeroModelView : public CallbackView {
 public:
  HeroModelView(const Rect&, shared_ptr<Hero>, IDeployHelper*);
  void UpdateViews();
  bool IsSelected() { return deploy_no_ != 0; }

 private:
  shared_ptr<Hero> hero_;
  uint32_t deploy_no_;
  bool     required_unselectable_;
  TextView* tv_no_;
};

class HeroModelListView : public CompositeView {
 public:
  HeroModelListView(const Rect&, const vector<shared_ptr<Hero>>&, IDeployHelper*);
  vector<shared_ptr<Hero>> GetHeroesSelected() { return heroes_selected_; }

 private:
  vector<shared_ptr<Hero>> heroes_selected_;
};

// DeployView is a UI view for deploying heroes

class DeployView : public CompositeView {
 public:
  DeployView(const Rect&, const vector<shared_ptr<Hero>>&, IDeployHelper*);

 private:
  vector<shared_ptr<Hero>> hero_list_;
};

#endif // DEPLOY_VIEW_H_
