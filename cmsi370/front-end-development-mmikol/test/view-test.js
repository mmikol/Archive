describe('view tests', () => {
  beforeEach(() => {
    fixture.setBase('test')
    fixture.load('view.fixture.html')
    window.SpoonacularViewHandler.init()
  })

  afterEach(() => fixture.cleanup())

  const FETCH_COMPLETION_DELAY = 250

  describe('API calls', () => {
    beforeEach(() => {
      sinon.stub(window.ApiService, 'getRecipeInfo')
      window.ApiService.getRecipeInfo.returns(Promise.resolve({
        "extendedIngredients": [
          { "originalString": "1/2 teaspoon black pepper" },
          { "originalString": "1 pound of spaghetti, cooked al dente" },
          { "originalString": "1/2 cup fresh basil leaves, thinly sliced" },
          { "originalString": "1/4 cup fresh mint leaves, roughly chopped" },
          { "originalString": "1/4 cup fresh parsley, roughly chopped" },
          { "originalString": "10 cloves garlic, sliced very thin or minced" },
          { "originalString": "2/3 cup olive oil" },
          { "originalString": "1 1/2 teaspoons crushed red pepper flakes (add a little more if you really like the spice!)" },
          { "originalString": "2 teaspoons salt" },
          { "originalString": "2 1/2 cups tomato puree" }
        ],
        "id": 667024,
        "title": "Simple Spaghetti Fra Diavolo",
        "image": "https://spoonacular.com/recipeImages/667024-556x370.jpg",
        "analyzedInstructions": [{
          "steps": [
            { "step": "Fill a large stock pot with water and salt and place over a medium-high flame; bring to a rolling boil and add spaghetti; cook for 5-6 minutes, or until pasta is almost al dente." },
            { "step": "Drain and add to pasta. While your pasta is cooking, make your sauce!" },
            { "step": "Heat olive oil in a large skillet over medium flame." },
            { "step": "Add garlic and cook for 2-3 minutes, stirring frequently, until garlic is fragrant and just starting to turn golden." },
            { "step": "Add crushed red pepper, and stir." },
            { "step": "Add tomato puree, stir, and reduce heat to medium." },
            { "step": "Let cook for 8 minutes  stirring occasionally  or until the oil beings to rise and separate from the tomato puree." },
            { "step": "Mix in fresh herbs, salt, and pepper; taste and adjust seasoning as needed.Once pasta is cooked and drained, add it to the sauce and and stir to coat the noodles. Reduce heat to low, cover pan, and let pasta cook in the sauce for 2-3 minutes." },
            { "step": "Serve pasta with cheese, and eat at once!" }
          ]
        }]
      }))
      window.SpoonacularViewHandler.init()
    })

    afterEach(() => window.ApiService.getRecipeInfo.restore())

    it('should populate a list with 10 ingredients', done => setTimeout(() => {
      expect($('#ingredientList').children().length).toBe(10)
      done()
    }, FETCH_COMPLETION_DELAY))

    describe('failed API call', () => {
      beforeEach(() => {
        window.ApiService.getRecipeInfo.returns(Promise.reject('Mock failure'))
        window.SpoonacularViewHandler.init()
      })

      it('should display an alert when the API call fails', done => setTimeout(() => {
        expect($('figure').find('.alert.alert-danger').length).toBe(1)
        done()
      }, FETCH_COMPLETION_DELAY))
    })
  })
})
