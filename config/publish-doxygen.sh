REPO_PATH=git@github.com:SJPMechaEagles/InTheZoneA.git
HTML_PATH=build/doc/html
COMMIT_USER="Auto Doc Bot"
COMMIT_EMAIL="cjerrett18@stjohnsprep.org"
CHANGESET=$(git rev-parse --verify HEAD)

rm -rf ${HTML_PATH}
mkdir -p ${HTML_PATH}
git clone -b gh-pages "${REPO_PATH}" --single-branch ${HTML_PATH}

cd ${HTML_PATH}
git rm -rf .
cd -

doxygen config/Doxyfile 
cd ${HTML_PATH}
git add .
git config user.name "${COMMIT_USER}"
git config user.email "${COMMIT_EMAIL}"
git commit -m "Automated documentation build for changeset ${CHANGESET}."
git push origin gh-pages
cd -