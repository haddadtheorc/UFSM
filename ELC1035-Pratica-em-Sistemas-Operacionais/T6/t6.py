import unittest
from selenium import webdriver
from selenium.webdriver.common.keys import Keys
from webdriver_manager.chrome import ChromeDriverManager
from selenium.webdriver.chrome.options import Options

class FlaskSearch(unittest.TestCase):

    def setUp(self):
        
        chrome_options = Options()
        chrome_options.add_experimental_option("detach", True)
        self.driver = webdriver.Chrome(ChromeDriverManager(version="96.0.4664.45").install(), chrome_options=chrome_options)

    def task_1(self, driver, test_user):
        # 1- Registrar um usuário no blog.
        elem = driver.find_element_by_link_text("Register")
        elem.send_keys(Keys.ENTER)
        elem = driver.find_element_by_name("username")
        elem.send_keys(test_user[0])
        elem = driver.find_element_by_name("password")
        elem.send_keys(test_user[1])
        elem = driver.find_element_by_css_selector("input[value='Register'")
        elem.send_keys(Keys.ENTER)

    def task_2(self, driver, test_user):
        # 2 - Fazer login do novo usuário
        elem = driver.find_element_by_link_text("Log In")
        elem.send_keys(Keys.ENTER)
        elem = driver.find_element_by_name("username")
        elem.send_keys(test_user[0])
        elem = driver.find_element_by_name("password")
        elem.send_keys(test_user[1])
        elem = driver.find_element_by_css_selector("input[value='Log In'")
        elem.send_keys(Keys.ENTER)

    def task_3(self, driver, test_post):
        # 3 - Criar um novo Post
        elem = driver.find_element_by_partial_link_text("New")
        elem.send_keys(Keys.ENTER)
        elem = driver.find_element_by_name("title")
        elem.send_keys(test_post[0])
        elem = driver.find_element_by_name("body")
        elem.send_keys(test_post[1])
        elem = driver.find_element_by_css_selector("input[value='Save'")
        elem.send_keys(Keys.ENTER)


    def test_flask(self):
        driver = self.driver
        driver.get("http://127.0.0.1:5000/")
        self.assertIn("Flask", driver.title)

        test_user=["user_novo", "user_novo_1234"]
        test_post=["test_post_title_user_novo", "user_novoTata\nTata\nTata\nLOLOLO\nLULULU"]

        self.task_1(driver, test_user)
        self.task_2(driver, test_user)
        self.task_3(driver, test_post)
        
        assert "No results found." not in driver.page_source

    # def tearDown(self):
    #     self.driver.close()

if __name__ == "__main__":
    unittest.main()