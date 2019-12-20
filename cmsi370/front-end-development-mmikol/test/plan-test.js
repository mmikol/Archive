describe('meal plan tests', () => {
  beforeEach(() => {
    fixture.setBase('test')
    fixture.load('plan.fixture.html')
    window.SpoonacularPlanHandler.init()
  })

  afterEach(() => fixture.cleanup())

  it('starts with an populated dice container', () => {
    expect($('#diceContainer').children().length).toEqual(1)
  })

  it('starts with an unpopulated meal plan table', () => {
    expect($('#dayMeals').children().length).toEqual(0)
  })

  const FETCH_COMPLETION_DELAY = 250

  describe('successful API calls', () => {
    beforeEach(() => {
      sinon.stub(window.ApiService, 'createMealPlan')
      window.ApiService.createMealPlan.returns(Promise.resolve({
        "items": [
          { "value": "{\"id\":715497,\"imageType\":\"jpg\",\"title\":\"Berry Banana Breakfast Smoothie\"}" },
          { "value": "{\"id\":649496,\"imageType\":\"jpg\",\"title\":\"Lemon and Arënkha Msc Risotto With Anchovy-Fried Crumbs\"}" },
          { "value": "{\"id\":644917,\"imageType\":\"jpg\",\"title\":\"Gnocchi and Wilted Spinach Salad\"}" },
          { "value": "{\"id\":634006,\"imageType\":\"jpg\",\"title\":\"Banana Bread\"}" },
          { "value": "{\"id\":651646,\"imageType\":\"jpg\",\"title\":\"Mexican Lasagna with Chicken & Black Bean\"}" },
          { "value": "{\"id\":633830,\"imageType\":\"jpg\",\"title\":\"Baked Swedish Pancake\"}" },
          { "value": "{\"id\":636087,\"imageType\":\"jpg\",\"title\":\"Waffles\"}" },
          { "value": "{\"id\":665446,\"imageType\":\"jpg\",\"title\":\"X-Country Double Lobster Risotto\"}" },
          { "value": "{\"id\":633744,\"imageType\":\"jpg\",\"title\":\"Baked Potatoes with Creamy Mushroom Ragout\"}" },
          { "value": "{\"id\":635507,\"imageType\":\"jpg\",\"title\":\"Blueberry Overload Muffins\"}" },
          { "value": "{\"id\":655269,\"imageType\":\"jpg\",\"title\":\"Peanut Butter Chocolate Cream Pie\"}" },
          { "value": "{\"id\":716300,\"imageType\":\"jpg\",\"title\":\"Plantain Pizza\"}" },
          { "value": "{\"id\":1100990,\"imageType\":\"jpg\",\"title\":\"Blueberry, Chocolate & Cocao Superfood Pancakes - Gluten-Free/Paleo/Vegan\"}" },
          { "value": "{\"id\":511728,\"imageType\":\"jpg\",\"title\":\"Pasta Margherita\"}" },
          { "value": "{\"id\":715595,\"imageType\":\"jpg\",\"title\":\"Cheesiest Bowtie Mac and Cheese\"}" },
          { "value": "{\"id\":635649,\"imageType\":\"jpg\",\"title\":\"Bon \“Apple\” Tite Cinnamon Rolls\"}" },
          { "value": "{\"id\":642540,\"imageType\":\"jpg\",\"title\":\"Falafel Burgers\"}" },
          { "value": "{\"id\":632935,\"imageType\":\"jpg\",\"title\":\"Asparagus Lemon Risotto\"}" },
          { "value": "{\"id\":633970,\"imageType\":\"jpg\",\"title\":\"Banana & Oreo Muffin\"}" },
          { "value": "{\"id\":655570,\"imageType\":\"jpg\",\"title\":\"Penne Con Funghi E Melanzane (Penne With Mushrooms and Eggplant)\"}" },
          { "value": "{\"id\":157272,\"imageType\":\"jpg\",\"title\":\"Pomegranate-Nutella Waffles\"}" }
        ]
      }))
      $('form.randomForm').submit()
    })

    afterEach(() => window.ApiService.createMealPlan.restore())

    it('should call API with timeFrame argument', () =>
      expect(window.ApiService.createMealPlan.firstCall.args[0]).toEqual({ timeFrame: 'week' })
    )

    it('should populate the table with 7 meals (for 7 days)', done => setTimeout(() => {
      expect($('#dayMeals').children().length).toBe(7)
      done()
    }, FETCH_COMPLETION_DELAY))
  })

  describe('failed API calls', () => {
    beforeEach(() => {
      sinon.stub(window.ApiService, 'createMealPlan')
      window.ApiService.createMealPlan.returns(Promise.reject('Mock failure'))
      $('form.randomForm').submit()
    })

    afterEach(() => window.ApiService.createMealPlan.restore())

    it('should display an alert when the API call fails', done => setTimeout(() => {
      expect($('#mealPlanTable').find('.alert.alert-danger').length).toBe(1)
      done()
    }, FETCH_COMPLETION_DELAY))
  })
})