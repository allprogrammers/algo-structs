node* add(node* root,int key)
{
    if(root!=NULL)
    {
        node* new = malloc(sizeof(node));
        new->key=key;
        new->count = 1;
        return new;
    }
    if(root.key==key)
        return root;
    if(root.key<key)
    {
        root->right = add(root->right,key);
        root->right->parent = root;
    }
    if(root.key>key)
    {
        root->left = add(root->left,key);
        root->left->parent = root;
    }
    root->count = root->right->count+root->left->count+1;
    return root;
}


node* floor(node* root,int key)
{
    if(root==NULL)
        return NULL;
    if(root->key == key)
        return root;
    if(root->key>key)
        return floor(root->left,key);
    //if(root->key<key)
    node* another = floor(root->right,key)
    if(another)
        return another;
    return root;
}

node* ceiling(node* root,int key)
{
    if(root==NULL)
        return NULL;
    if(root->key == key)
        return root;
    if(root->key < key)
        return ceiling(root->right,key);
    node* another = ceiling(root->left,key);
    if(another)
        return another;
    return root;
}

int size(node* root)
{
    if(!root)
        return 0;
    return root.count;
}

node* rank(node* root,int key)
{
    if(root == NULL)
        return 0;
    if(root->key==key)
        return size(root->left)-1;
    if(root->key<key)
        return size(root->left)+rank(root->right,key)+1;
    if(root->key>key)
        return rank(root->left);
        
}

node* succ(node* root,int key)
{
    if(!root)
        return NULL;
    if(root->key>key)
        return succ(root->left,key);
    else if(root->key<key)
        return succ(root->right,key);
    if(root->right)
        return bstmin(root->right);
    node* start = root;
    while(start)
    {
        start = start->parent;
        if(start->left==root)
            return start;
    }
    return NULL;
}

node* pred(node* root,int key)
{
    if(!root)
        return NULL;
    if(root->key>key)
        return succ(root->left,key);
    else if(root->key<key)
        return succ(root->right,key);
    if(root->left)
        return bstmax(root->right);
    node* start = root;
    while(start)
    {
        start = start->parent;
        if(start->right==root)
            return start;
    }
    return NULL;
}

node* bstmin(node* root)
{
    if(!root)
        return NULL;
    if(root->left)
        return root;
    return bstmin(root->left);
}

node* bstmax(node* root)
{
    if(!root)
        return NULL;
    if(root->right)
        return root;
    return bstmax(root->right);
}

node* select(node* root,int k)
{
    if(!root)
        return NULL;
    if(size(root->left)==k)
        return root;
    if(size(root->left>k)
        return select(root->left,k);
    return select(root->right,k-size(root->left)-1);
}

node* addtoroot(node* root,int key)
{
    if(!root)
    {
        node* new = malloc(sizeof(node));
        new->key = key;
        return new;
    }
    if(root->key < key)
    {
        root->right = addtoroot(root->right,key);
        return rotac(root);
    }
    if(root->key > key)
    {
        root->left =addtoroot(root->left,key);
        return rotc(root);
    }
    return root;

}

node* deletemax(node* root)
{
    //TODO delete partitioning
    if(root->right)
    {
        root->right = deletemax(root->right);
        return root
    }
    node* temp = root->left;
    free(root);
    return temp;
}

node* delete(node* root,int key)
{
    if(!root)
        return NULL;
    if(root->key<key)
        root->right = delete(root->right,key);
    else if(root->key>key)
        root->left = delete(root->left,key);
    else
    {
        if(root->left!=NULL) return root->right;
        if(root->right!=NULL) return root->left;
        node* successor = bstmax(root->left);
        root->left = deletemax(root->left);
    }
    return root;

    
}

node* rotac(node* ntr)
{
    node* child = ntr->right;
    ntr->right = child->left;
    child->left = ntr;
    return child;
}

node* rotc(node* ntr)
{
    node* child = ntr->left;
    ntr->left = child->right;
    child->right = ntr;
    return child;
}


