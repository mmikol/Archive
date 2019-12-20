/* eslint-disable */

/*
NOTE: for almost all functions, the results are simplified to return only what is needed for the mockup 
otherwise there would be a lot of data. The structure of the data is still maintained.
*/

(() => {
  const searchRecipes = () => Promise.resolve({
    "results": [
      {
        "id": 667024,
        "title": "Simple Spaghetti Fra Diavolo",
      },
      {
        "id": 428687,
        "title": "Spaghetti Sauce",
      },
      {
        "id": 570186,
        "title": "Spaghetti & Meatball Cups",
      },
      {
        "id": 757883,
        "title": "Spaghetti with Lemon and Toasted Walnuts",
      },
      {
        "id": 988122,
        "title": "Spaghetti Carbonara",
      },
      {
        "id": 715263,
        "title": "Spaghetti with No-Cook Tomato Sauce and Hazelnuts",
      },
      {
        "id": 627535,
        "title": "Slow Cooker Cheesy Spaghetti with Turkey Sausage",
      },
      {
        "id": 535914,
        "title": "Threaded Spaghetti Hot Dog Bites with Homemade Marinara Sauce",
      },
      {
        "id": 627793,
        "title": "Spaghetti with Creamy Butternut Leek Parmesan Sauce Skinnytaste",
      },
      {
        "id": 517120,
        "title": "Baked Lemon Spaghetti",
      }
    ]
  })

  const createMealPlan = () => Promise.resolve({
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
  })

  const getRecipeInfo = () => Promise.resolve({
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
  })

  const getNutritionFacts = () => Promise.resolve({
    calories: "577",
    carbs: "53g",
    fat: "37g",
    protein: "10g"
  })

  window.ApiService = {
    apiHost: () => { },
    searchRecipes,
    createMealPlan,
    getRecipeInfo,
    getNutritionFacts
  }
})()